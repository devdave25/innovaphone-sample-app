
/// <reference path="~/sdk/web1/lib1/innovaphone.lib1.js" />
/// <reference path="~/sdk/web1/ui1.lib/innovaphone.ui1.lib.js" />

var innovaphone = innovaphone || {};
innovaphone.ui1 = innovaphone.ui1 || {};

innovaphone.ui1.PopupStyles = innovaphone.ui1.PopupStyles || function (background, header, main, closer) {
    this.background = background;
    this.header = header;
    this.main = main;
    this.closer = closer;
}

innovaphone.ui1.Popup = innovaphone.ui1.Popup || function (style, styles, h) {

    var dragX = 0;  // start position of the moving object
    var dragY = 0;
    var posX = 0;   // mouse position
    var posY = 0;
    var that = this;

    var background = document.createElement("div");
    innovaphone.lib1.addClass(background, styles.background);
    background.setAttribute("style", "position:absolute; z-index:1; top:0px; bottom:0px; left:0px; right:0px");
    document.body.appendChild(background);

    this.createNode("div", style, null, styles.main);

    background.appendChild(this.container);

    var header = this.add(new innovaphone.ui1.Div("position:absolute; top:0px; left:0px; right:0px; font-size:14px; font-weight:bold; text-align:center; cursor:pointer; height:" + h + "px", null, styles.header));

    var content = this.add(new innovaphone.ui1.Div("position:absolute; left:0px; right:0px; bottom:0px; top:" + h + "px"));

    var closer = this.add(new innovaphone.ui1.Div("position:absolute; cursor:pointer; z-index:1", null, styles.closer));
    closer.addEvent("click", close);

    var eventStart = innovaphone.lib1.isTouch ? "touchstart" : "mousedown";
    var eventMove = innovaphone.lib1.isTouch ? "touchmove" : "mousemove";
    var eventStop = innovaphone.lib1.isTouch ? "touchend" : "mouseup";

    header.makeUnselectable();
    header.addEvent(eventStart, mouseDown);

    function mouseDown(event) {
        document.body.addEventListener(eventMove, mouseMove);
        document.body.addEventListener(eventStop, mouseUp);
        if (innovaphone.lib1.isTouch) {
            var e = event || window.event;
            dragX = e.touches[0].pageX;
            dragY = e.touches[0].pageY;
        }
        else {
            dragX = event.offsetX;
            dragY = event.offsetY;
        }
    }

    function mouseMove(event) {
        var e = null;
        if (innovaphone.lib1.isTouch) e = event.touches[0];
        else e = event || window.event;
        that.container.style.left = (e.pageX - dragX) + "px";
        that.container.style.top = (e.pageY - dragY) + "px";
        e.stopPropagation();
    }

    function mouseUp(event) {
        document.body.removeEventListener(eventMove, mouseMove);
        document.body.removeEventListener(eventStop, mouseUp);
    }
    
    function close() {
        document.body.removeChild(background);
    }

    this.close = function () {
        close();
    }

    this.header = header;
    this.content = content;
    this.closer = closer;
}

innovaphone.ui1.Popup.prototype = innovaphone.ui1.nodePrototype;