var innovaphone = innovaphone || {};
innovaphone.ui1 = innovaphone.ui1 || {};
innovaphone.ui1.Switch = innovaphone.ui1.Switch || function (style, height, width, value, cl, foreground, backgroundOff, backgroundOn) {
    var that = this;
    that.backgroundOff = backgroundOff ? backgroundOff : "#7b7b7b";
    that.backgroundOn = backgroundOn ? backgroundOn : "#7CB270";
    that.foreground = foreground ? foreground : (cl ? "" : "white");
    that.width = width ? width : "35px";
    that.height = height ? height : "20px";
    var sliderWidth = (parseInt(that.width) / 1.9 - 4) + "px";
    var sliderHeight = (parseInt(that.height) - 6) + "px";
    var sliderTranslation = ((parseInt(that.width) - parseInt(sliderWidth)) - 6) + "px";
    var labelHeight = (parseInt(that.height) / 3);

    function draw() {
        slider.style.transform = that.container.state ? "translateX(" + sliderTranslation + ")" : "translateX(0px)";
        box.container.style.backgroundColor = that.container.state ? that.backgroundOn : that.backgroundOff;
        that.container.style.filter = that.container.disabled ? "grayscale(50%) contrast(50%)" : "";
        that.container.style.cursor = that.container.disabled ? "" : "pointer";
        that.container.tabIndex = "";
    }

    that.getValue = function () { return that.container.state }
    that.setValue = function (value) { that.container.state = value ? true : false; draw() }
    that.setDisabled = function (value) { that.container.disabled = value ? true : false; draw() }
    that.setTooltip = function (value) { that.container.setAttribute("title", value) }

    var box = that.createNode("div", "position: relative; -webkit-transition: 0.2s; transition: 0.2s; border-radius: 1px; width: " + that.width + "; max-width: " + that.width + "; min-width: " + that.width + "; height: " + that.height + "; min-height: 8px; " + style, null, cl);

    var label = document.createElement("div");
    var labelOn = document.createElement("div");
    var labelOff = document.createElement("div");
    label.style.cssText = "position: absolute; top: 0; left: 3px; bottom: 0; right: 3px; z-index: 10; padding: 0 calc(" + parseInt(that.width) + "px / 8); display: inline-flex; align-items: center; justify-content: space-between; font-size: 12px; opacity: 0.6; color: " + that.foreground + "";
    labelOn.style.cssText = "background-color: " + that.foreground + "; height: " + parseInt(labelHeight) + "px; width: 2px; margin-left: calc(" + sliderWidth + " / 4 - 3px);";
    labelOff.style.cssText = "border: 1px solid; border-color: " + that.foreground + "; border-radius: 50%; height: " + labelHeight + "px; width: " + labelHeight + "px; margin-right: calc(" + sliderWidth + " / 4 - " + labelHeight + "px);";

    var slider = document.createElement("div");
    slider.style.cssText = "position: absolute; top: 3px; left: 3px; -webkit-transition: transform 0.2s ease-out; transition: transform 0.2s ease-out; min-height: 2px; border-radius: 1px; box-shadow: 1px 1px 6px #515151;";
    slider.style.width = sliderWidth;
    slider.style.height = sliderHeight;
    slider.style.backgroundColor = that.foreground;

    label.appendChild(labelOn);
    label.appendChild(labelOff);
    box.container.appendChild(label);
    box.container.appendChild(slider);

    that.addEvent("click", input);
    that.addEvent("keydown", input);

    function input(e) {
        if (e && (e.type == "click" || e.keyCode == innovaphone.ui1.lib.keyCodes.enter || e.keyCode == innovaphone.ui1.lib.keyCodes.space) &&
            !that.container.disabled) {
            that.container.state = that.container.state ? false : true;
            draw();
            // call user's "change" handler (if any)
            var onchange = that.events.find(function (v) { return v.type == "change" && v.handler });
            if (onchange) onchange.handler(e);
        }
    };

    that.setValue(value);
}
innovaphone.ui1.Switch.prototype = innovaphone.ui1.nodePrototype;
