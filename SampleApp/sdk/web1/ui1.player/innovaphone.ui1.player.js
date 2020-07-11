
/// <reference path="../ui.lib1/innovaphone.ui1.lib.js" />

innovaphone = innovaphone || {};
innovaphone.ui1 = innovaphone.ui1 || {};

innovaphonePlayers = new Array();

innovaphone.ui1.PlayerIconConfig = innovaphone.ui1.PlayerIconConfig || function (iconSpriteUrl, playIconPosX, playIconPosY, pauseIconPosX, pauseIconPosY, sliderIconPosX, sliderIconPosY) {
    this.iconSpriteUrl = iconSpriteUrl;
    this.playIconPosX = playIconPosX;
    this.playIconPosY = playIconPosY;
    this.pauseIconPosX = pauseIconPosX;
    this.pauseIconPosY = pauseIconPosY;
    this.sliderIconPosX = sliderIconPosX;
    this.sliderIconPosY = sliderIconPosY;
}


innovaphone.ui1.Player = innovaphone.ui1.Player || function (style, cl, iconConfig, srcAudio) {
    this.createNode("div", style, 0, cl);
    var container = this.container;
    var that = this;
    var pressed = 0;
    var playing = 0;

    innovaphonePlayers.push(this);

    container.style.height = 20 + "px";

    var eventStart = (innovaphone.lib1.isTouch ? "touchstart" : "mousedown");
    var eventStop = (innovaphone.lib1.isTouch ? "touchend" : "mouseup");
    var eventMove = (innovaphone.lib1.isTouch ? "touchmove" : "mousemove");

    var audio = document.createElement("audio");
	audio.setAttribute("preload", "auto");	
    audio.src = srcAudio;

    
    var totalLengthUi = this.add(new innovaphone.ui1.Div("position:absolute; top:0px; right:0px; width:30px; height:" + container.style.height, "0:00", null));
    var playUi = this.add(new innovaphone.ui1.Div("position:absolute; left:0px; top:0px; cursor:pointer; margin-top:4px; margin-left:2px; width:14px; height:14px; overflow:hidden; background-image:url(" + "'" + iconConfig.iconSpriteUrl + "'" + "); background-position:" + iconConfig.playIconPosX + "px" + " " + iconConfig.playIconPosY + "px", null, null));
    var pauseUi = this.add(new innovaphone.ui1.Div("position:absolute; left:0px; top:0px; cursor:pointer; display:none; margin-top:4px; margin-left:2px; width:14px; height:14px; overflow:hidden; background-image:url(" + "'" + iconConfig.iconSpriteUrl + "'" + "); background-position:" + iconConfig.pauseIconPosX + "px" + " " + iconConfig.pauseIconPosY + "px", null, null));
    var sliderUi = this.add(new innovaphone.ui1.Div("position:absolute; top:0px; left:20px; right:40px; height:" + container.style.height, 0));
    var sliderIconUi = sliderUi.add(new innovaphone.ui1.Div("position:absolute; left:0px; top:4px; cursor:pointer; margin-top:4px; width:8px; height:8px; overflow:hidden; background-image:url(" + "'" + iconConfig.iconSpriteUrl + "'" + "); background-position:" + iconConfig.sliderIconPosX + "px" + " " + iconConfig.sliderIconPosY + "px", null, null));
    var sliderLineUi = sliderUi.add(new innovaphone.ui1.Div("position:relative; left:0px; right:0px; height:1px; top:" + parseInt(container.style.height)/2 + "px", null, null));
    sliderLineUi.container.style.backgroundColor = "white";

    sliderIconUi.addEvent(eventStart, function (event) {
        pressed = 1;
        audio.pause();
    });

    sliderIconUi.addEvent(eventStop, function (event) {
        pressed = 0;
        if (playing) audio.play()
    });


    playUi.addEvent("click", function () {
        for (var i = 0; i < innovaphonePlayers.length; i++) {
            innovaphonePlayers[i].stopPlaying();
        }
        audio.play();
        playing = 1;
        that.audioIsPlaying();
    });

    pauseUi.addEvent("click", function () {
        playing = 0;
        audio.pause();
    });

    audio.addEventListener("timeupdate", function () {
        var currentdisplay = that.container.style.display;
        that.container.style.display = "";
        var containerBounds = sliderUi.container.getBoundingClientRect();
        that.container.style.display = currentdisplay;
        var time = Math.round((parseInt(containerBounds.width) * Number((audio.currentTime) / (audio.duration)))); 
        if (playing && time) {
            sliderIconUi.container.style.left = time + "px";
        }
    });

    audio.addEventListener("ended", function () {
        audio.currentTime = 0;
        sliderIconUi.container.style.left = 0 + "px";
        playing = 0;
    });

    sliderUi.addEvent(eventMove, function (event) {
        if (pressed) {
            var containerBounds = sliderUi.container.getBoundingClientRect();
            if (event.clientX <= containerBounds.left) {
                sliderIconUi.container.style.left = 0 + "px";
            }
            if ((event.clientX - containerBounds.left) >= 0 && (event.clientX - containerBounds.left) <= containerBounds.width) {
                sliderIconUi.container.style.left = event.clientX - containerBounds.left + "px";
            }
            if ((event.clientX - containerBounds.left) > containerBounds.width) {
                sliderIconUi.container.style.left = containerBounds.width + "px";
            }
            audio.currentTime = Number(parseInt(sliderIconUi.container.style.left) / parseInt(containerBounds.width)) * audio.duration;
        }
    });

    sliderUi.addEvent("click", function (event) {
        audio.pause();
        var containerBounds = sliderUi.container.getBoundingClientRect();
        if (event.clientX <= containerBounds.left) {
            sliderIconUi.container.style.left = 0 + "px";
        }
        if ((event.clientX - containerBounds.left) >= 0 && (event.clientX - containerBounds.left) <= containerBounds.width) {
            sliderIconUi.container.style.left = event.clientX - containerBounds.left + "px";
        }
        if ((event.clientX - containerBounds.left) > containerBounds.width) {
            sliderIconUi.container.style.left = containerBounds.width + "px";
        }
        audio.currentTime = Number(parseInt(sliderIconUi.container.style.left) / parseInt(containerBounds.width)) * audio.duration;
        if (playing) audio.play();
    });

    audio.addEventListener("playing", function () {
        playUi.container.style.display = "none";
        pauseUi.container.style.display = "";
    });

    audio.addEventListener("pause", function () {
        playUi.container.style.display = "";
        pauseUi.container.style.display = "none";
    });

    audio.addEventListener("durationchange", function () {
        var e = new Date(parseInt(audio.duration) * 1000);
        var lengthString = e.getMinutes() + ":" + ("0" + e.getSeconds()).slice(-2);
        totalLengthUi.container.innerText = lengthString;
    });

    this.stopPlaying = function () {
        playing = 0;
        audio.pause();
    }

    this.audioIsPlaying = function () {};
};

innovaphone.ui1.Player.prototype = innovaphone.ui1.nodePrototype;