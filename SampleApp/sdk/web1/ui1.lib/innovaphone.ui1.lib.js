
/// <reference path="../lib1/innovaphone.lib1.js" />

var innovaphone = innovaphone || {};
innovaphone.ui1 = innovaphone.ui1 || {};

innovaphone.ui1.nodePrototype = {
    addText: function (text) {
        this.container.innerText = text || "";
        return this;
    },

    addHTML: function (html) {
        this.container.innerHTML = html;
        return this;
    },

    add: function (node, before) {
        this.container.insertBefore(node.container, before ? before.container || before : null);
        return node;
    },

    rem: function (node) {
        if (this.container == node.container.parentNode) {
            this.container.removeChild(node.container);
            return node;
        }
    },

    clear: function () {
        this.container.innerHTML = "";
        return this;
    },

    firstChild: function () {
        return this.container.firstChild;
    },
    
    Listener: function (c, type, handler, obj) {
        c.addEventListener(type, on);

        function on(e) {
            handler(e, obj);
        }

        this.rem = function () {
            c.removeEventListener(type, on);    
        }

        this.type = type;
        this.handler = handler;
        this.obj = obj;
    },

    addEvent: function (type, handler, obj) {
        this.events = this.events || [];
        this.events.push(new this.Listener(this.container, type, handler, obj === undefined ? this : obj));
        return this;
    },

    remEvent: function (type, handler) {
        if (this.events) {
            var index = this.events.findIndex(function (v) { return v.type == type && (handler ? v.handler == handler : true); });
            if (index > -1) {
                this.events[index].rem();
                this.events.splice(index, 1);
            }
        }
        return this;
    },

    setClass: function (className) {
        this.container.className = className;
        return this;
    },

    addClass: function (className) {
        this.container.classList.add(className);
        return this;
    },

    remClass: function (className) {
        this.container.classList.remove(className);
        return this;
    },

    hasClass: function (className) {
        return this.container.classList.contains(className);
    },

    addTranslation: function (languages, id, property, args) {
        languages.create(this, property, id, args);
        return this;
    },

    createTranslation: function (languages, id, property, args) {
        return languages.create(this, property, id, args);
    },
    
    setNoSelect: function () {
        this.container.style.webkitTouchCallout = "none";
        this.container.style.webkitUserSelect = "none";
        this.container.style.khtmlUserSelect = "none";
        this.container.style.MozUserSelect = "none";
        this.container.style.msUserSelect = "none";
        this.container.style.userSelect = "none";
        this.container.style.draggable = false;
        this.container.onselectstart = function () { return false; }
        this.container.ondragstart = function () { return false; }
        return this;
    },
    
    makeUnselectable: function () {
        this.container.style.MozUserSelect = "none";
        this.container.style.webkitUserSelect = "none";
        this.container.style.webkitTouchCallout = "none";
        this.container.setAttribute("unselectable", "on");
        return this;
    },

    setDisabled: function (state) {
        this.container.disabled = state !== false;
        return this;
    },

    createNode: function (type, style, content, cl) {
        if (type == "body") {
            this.container = document.body;
            this.container.addEventListener("dragover", function (e) {
                e = e || event;
                e.stopPropagation();
                e.preventDefault();
                e.dataTransfer.dropEffect = "none";
            });
        }
        else this.container = document.createElement(type);
        if (style) this.container.setAttribute("style", style);
        if (content) {
            if (content.container) this.container.appendChild(content.container);
            else this.container.innerText = content;
        }
        if (cl) this.container.setAttribute("class", cl);
        return this;
    },

    testId: function (id) {
        if (id) this.container.setAttribute("id", "test-" + id);
        else this.container.removeAttribute("id");
        return this;
    }
}

innovaphone.ui1.Node = innovaphone.ui1.Node || function (type, style, content, cl) {
    this.createNode(type, style, content, cl);
}

innovaphone.ui1.Node.prototype = innovaphone.ui1.nodePrototype;

innovaphone.ui1.Div = innovaphone.ui1.Div || function (style, content, cl) {
    this.createNode("div", style, content, cl);
}

innovaphone.ui1.Div.prototype = innovaphone.ui1.nodePrototype;

innovaphone.ui1.Input = innovaphone.ui1.Input || function (style, value, placeHolder, maxLength, type, cl) {
    var that = this,
        originalValue = value;

    this.createNode("input", style, null, cl);
    if (value) setValue(value);
    if (placeHolder) this.container.placeholder = placeHolder;
    if (maxLength) this.container.maxLength = maxLength;
    if (type) {
        this.container.setAttribute("type", type);
    }

    function changed(noTrim) {
        if (type == "checkbox") return that.container.checked != originalValue;
        else if (type == "password" || noTrim) return that.container.value != originalValue;
        else return that.container.value.trim() != originalValue;
    }

    function setValue(value, overrideOriginalValue) {
        if (type == "checkbox") that.container.checked = value;
        else that.container.value = value;
        if (overrideOriginalValue) {
            originalValue = value;
        }
        return that;
    }

    function getValue(noTrim) {
        switch (type) {
            case "checkbox":
                return that.container.checked;
            case "number":
                if (!that.container.value || that.container.value.length == 0) return 0;
                else return parseInt(that.container.value);
            case "password":
                return that.container.value;
            default:
                if (!noTrim && that.container.value != that.container.value.trim()) {
                    that.container.value = that.container.value.trim();
                }
                return that.container.value;
        }
    }

    this.changed = changed;
    this.setValue = setValue;
    this.getValue = getValue;
}
innovaphone.ui1.Input.prototype = innovaphone.ui1.nodePrototype;

innovaphone.ui1.Checkbox = innovaphone.ui1.Checkbox || function (style, value, cl, background, foreground, backgroundOff, inherit) {
    var that = this;
    that.background = background ? background : "gray";
    that.foreground = foreground ? foreground : "white";
    that.backgroundOff = backgroundOff ? backgroundOff : that.background;
    var svg = '<svg style="position:relative;width:14px;fill:' + that.foreground + ';" viewBox="0 0 20 20"><path d="M6.67,17.5,0,10.81,1.62,9.18l5.05,5.06L18.38,2.5,20,4.13Z"></path></svg>';
    function draw() {
        that.container.checked || (that.container.checked == undefined && inherit) ? that.addHTML(svg) : that.clear();
        box.container.style.backgroundColor = that.container.checked || (that.container.checked == undefined && inherit) ? that.background : that.backgroundOff;
        that.container.style.filter = that.container.disabled || that.container.checked == undefined ? "grayscale(50%) contrast(50%)" : "";
        that.container.style.cursor = that.container.disabled ? "" : "pointer";
    }
    that.getValue = function () { return that.container.checked }
    that.setValue = function (value) {
        if (value) {
            that.container.checked = true;
            that.container.setAttribute("checked", "on");
        }
        else if(!value && inherit == undefined) {
            that.container.checked = false;
            that.container.removeAttribute("checked");
        }
        else {
            that.container.checked = value;
            that.container.removeAttribute("checked");
        }
        draw();
    }
    that.setDisabled = function (value) { that.container.disabled = value ? true : false; draw() }
    that.setTooltip = function (value) { that.container.setAttribute("title", value) }
    var box = that.createNode("div", "display:flex;align-items:center;justify-content:center;width:20px;height:20px;" + style, null, cl);
    box.container.tabIndex = "0";

    function click(e) {
        if (!that.container.disabled) {
            that.setValue(that.container.checked ? false : (that.container.checked == undefined || inherit == undefined ? true : undefined));
            // call user's "change" handler (if any)
            var onchange = that.events.find(function (v) { return (v.type == "change") && v.handler });
            if (onchange) onchange.handler(e, onchange.obj);
        }
    }

    that.addEvent("click", function (e) {
        click(e);
    });
    that.addEvent("keydown", function (e) {
        if (e.keyCode == innovaphone.lib1.keyCodes.space) {
            click(e);
        }
    });
    that.setValue(value);
}
innovaphone.ui1.Checkbox.prototype = innovaphone.ui1.nodePrototype;

innovaphone.ui1.cssVariablesSupported = innovaphone.ui1.cssVariablesSupported || function () {
    var div = document.createElement("div");
    div.style.display = "var(--innovaphone-ui1-cssvariablessupported)";
    document.body.appendChild(div);
    document.body.style.setProperty("--innovaphone-ui1-cssvariablessupported", "inline-block");
    var supported = getComputedStyle(div, null).getPropertyValue('display') == "inline-block";
    document.body.removeChild(div);
    document.body.style.removeProperty("--innovaphone-ui1-cssvariablessupported");
    return supported;
};

innovaphone.ui1.CssVariables = innovaphone.ui1.CssVariables || function (sets, current, element) {
    this.sets = sets;
    this.current = current;
    this.element = element || document.body;
    this.activate(current);
};

innovaphone.ui1.CssVariables.prototype = {
    activate: function (id) {
        this.current = this.sets[id] ? id : Object.keys(this.sets)[0];
        for (var variable in this.sets[this.current]) this.element.style.setProperty(variable, this.sets[this.current][variable]);
    },
    toggle: function () {
        var ids = Object.keys(this.sets),
            index = ids.indexOf(this.current);
        this.activate(ids[index > -1 ? (index + 1) % ids.length : 0]);
    }
};

innovaphone.ui1.lib = innovaphone.ui1.lib || (function () {

    var isTouch = (('ontouchstart' in window) || (navigator.msMaxTouchPoints > 0));
    var browser = getBrowserInfo();
    browser.touch = isTouch;

    function getBrowserInfo() {
        var ua = window.navigator.userAgent;
        if (ua.indexOf("myApps/") != -1) {
            if (ua.indexOf("Windows") != -1) return { name: "myApps for Windows", webkit: true };
            if (ua.indexOf("Android") != -1) return { name: "myApps for Android", webkit: true };
            if (ua.indexOf("iOS") != -1) return { name: "myApps for iOS", webkit: true };
            if (ua.indexOf("macOS") != -1) return { name: "myApps for macOS", webkit: true };
            return {};
        }
        else if (ua.indexOf("OPR/") != -1 || ua.indexOf("Opera/") != -1) return { name: "Opera", webkit: true };
        else if (ua.indexOf("Edge/") != -1) return { name: "Edge", webkit: false };
        else if (ua.indexOf("Firefox/") != -1) return { name: "Firefox", webkit: false };
        else if (ua.indexOf("Chromium/") != -1) return { name: "Chromium", webkit: true };
        else if (ua.indexOf("Chrome/") != -1) return { name: "Chrome", webkit: true };
        else if (ua.indexOf("Safari/") != -1) return { name: "Safari", webkit: true };
        else if (ua.indexOf("Trident/") != -1) return { name: "Internet Explorer", webkit: false };
        return {};
    }

    var keyCodes = {
        arrowDown: 40,
        arrowLeft: 37,
        arrowRight: 39,
        arrowUp: 38,
        pageUp: 33,
        pageDown: 34,
        end: 35,
        home:36,
        escape: 27,
        enter: 13,
        space: 32,
        tab: 9,
    };

    return {
        browser: browser,
        isTouch: isTouch,
        keyCodes: keyCodes
    }
})();
