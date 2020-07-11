/// <reference path="../lib1/innovaphone.lib1.js" />
/// <reference path="../ui1.lib/innovaphone.ui1.lib.js" />

innovaphone = innovaphone || {};
innovaphone.ui1 = innovaphone.ui1 || {};

innovaphone.ui1.AutoCompleteInputConfig = innovaphone.ui1.AutoCompleteInputConfig || function (inputStyle, inputCl, suggestionStyle, suggestionCl, suggestionHighlightCl, dropDownCl) {
    this.inputStyle = inputStyle;
    this.inputCl = inputCl;
    this.suggestionStyle = suggestionStyle;
    this.suggestionCl = suggestionCl;
    this.suggestionHighlightCl = suggestionHighlightCl;
    this.dropDownCl = dropDownCl;
}

innovaphone.ui1.AutoCompleteInput = innovaphone.ui1.AutoCompleteInput || function (style, cl, config) {
    /// <param name="config" type="innovaphone.ui1.AutoCompleteInputConfig"/>

    if (!config) {  // backward compatibility
        config = new innovaphone.ui1.AutoCompleteInputConfig();
    }
    this.createNode("div", style, "", cl);
    var width = 100,
        callBackOnChange = null,
        callBackCompleteValue = null,
        lastKeyCode = 0,
        separator = ',',
        useSpaces = true,
        container = this.container,
        inputBoxThis = this,
        //var inputBox = this.add(new innovaphone.ui1.Node("input", config.inputStyle, config.inputCl));
        inputBox = this.add(new innovaphone.ui1.Node("input", config.inputStyle, null, config.inputCl));

    inputBox.container.autocomplete = "off";
    inputBox.container.autocorrect = "off";
    inputBox.container.autocapitalize = "off";
    inputBox.container.spellcheck = false;
    
    function getCurrentValue() {
        var currentValue = inputBoxThis.value();
        var valueArray = currentValue.split(separator);
        return valueArray[valueArray.length - 1];

    }

    function setNewValue(newValue) {
        var currentValue = inputBoxThis.value(),
            lastComma = currentValue.lastIndexOf(separator),
            finalValue = currentValue.substring(0, lastComma + 1),
            toChop = currentValue.substring(lastComma + 1, currentValue.length),
            firstNonSpace = toChop.search(/\S|$/),
            lastSpace = toChop.lastIndexOf(" "),
            lastNonSpace = toChop.replace(/\s*$/, "").length;

        finalValue += toChop.substring(0, firstNonSpace);
        finalValue += newValue;
        if (lastNonSpace > 0) {
            finalValue += toChop.substring(lastNonSpace, toChop.length);
        }

        inputBoxThis.setValue(finalValue);
    }
    
    function AutoSuggestControl(textbox) {
        var that = this,
            cur = -1;

        this.createNode("div", "", "");
        
        function init() {
            textbox.onfocus = function (oEvent) {
                onFocus();
            }

            //assign the onkeyup event handler
            textbox.onkeyup = function (oEvent) {

                //check for the proper location of the event object
                if (!oEvent) {
                    oEvent = window.event;
                }

                //call the handleKeyUp() method with the event object
                handleKeyUp(oEvent);
            };

            //assign onkeydown event handler
            textbox.onkeydown = function (oEvent) {

                //check for the proper location of the event object
                if (!oEvent) {
                    oEvent = window.event;
                }

                //call the handleKeyDown() method with the event object
                handleKeyDown(oEvent);
            };

            //assign onblur event handler (hides suggestions)    
            textbox.onblur = function () {
                hideSuggestions();
            };

            //create the suggestions dropdown
            createDropDown();
        }

        function onFocus() {
            var cValue = getCurrentValue().trim();
            var cSuggestions = callBackOnChange(cValue.trim());
            if (cSuggestions === null) {
                return;
            }
            handleSuggestion(cSuggestions);
        }

        function autoSuggest(aSuggestions) {
            if (aSuggestions.length > 0) {
                showSuggestions(aSuggestions);
            } else {
                hideSuggestions();
            }
        }

        function createDropDown() {
            that.container.classList.add(config.dropDownCl);
            that.container.style.position = "absolute";
            that.container.style.width = width;
            that.container.style.height = "auto";
            that.container.style.clear = "both";
            that.container.style.padding = "0px";
            that.container.style.textAlign = "left";
            that.container.style.zIndex = 199;

            //this.container.style.visibility = "hidden";
            that.container.style.display = "none";

            that.container.onmousedown =
            that.container.onmouseup =
            that.container.onmouseover = function (oEvent) {
                oEvent = oEvent || window.event;
                var oTarget = oEvent.target || oEvent.srcElement;

                if (oEvent.type === "mousedown") {
                    setNewValue(oTarget.firstChild.nodeValue);
                    hideSuggestions();
                } else if (oEvent.type === "mouseover") {
                    highlightSuggestion(oTarget);
                } else {
                    textbox.focus();
                }
            };
        }

        function handleKeyDown(oEvent) {
            switch (oEvent.keyCode) {
                case innovaphone.lib1.keyCodes.arrowUp:
                    previousSuggestion();
                    oEvent.preventDefault();
                    break;
                case innovaphone.lib1.keyCodes.arrowDown:
                    nextSuggestion();
                    break;
                case innovaphone.lib1.keyCodes.enter:
                    hideSuggestions();
                    break;
            }

        }

        function handleKeyUp(oEvent) {
            var iKeyCode = oEvent.keyCode;
            if ((iKeyCode > innovaphone.lib1.keyCodes.insert || iKeyCode == innovaphone.lib1.keyCodes.backSpace) &&
                (iKeyCode < innovaphone.lib1.keyCodes.f1 || iKeyCode > innovaphone.lib1.keyCodes.f12)) {
                lastKeyCode = iKeyCode;
                if (callBackCompleteValue !== null)
                    callBackCompleteValue(inputBox.value());
                var cValue = getCurrentValue().trim();
                cur = -1;   // reset cur after retrieval of new options
                var cSuggestions = callBackOnChange(cValue.trim());
                if (cSuggestions === null) {
                    return;
                }

                handleSuggestion(cSuggestions);
            }
        }

        function handleSuggestion(cSuggestions) {
            var aSuggestions = [],
                iKeyCode = lastKeyCode,
                cValue = getCurrentValue().trim();

            for (var i = 0; i < cSuggestions.length; i++) {
                if (cSuggestions[i].indexOf(cValue.trim()) === 0) {
                    aSuggestions.push(cSuggestions[i]);
                }
            }
            autoSuggest(cSuggestions);
        }

        function hideSuggestions() {
            that.container.style.display = "none";
        }

        function highlightSuggestion (oSuggestionNode) {
            for (var i = 0; i < that.container.childNodes.length; i++) {
                var oNode = that.container.childNodes[i];
                if (oNode === oSuggestionNode) {
                    oNode.classList.add(config.suggestionHighlightCl);
                } else {
                    oNode.classList.remove(config.suggestionHighlightCl);
                }
            }
        }

        function nextSuggestion() {
            var cSuggestionNodes = that.container.childNodes,
                oldCur = cur;
            if (cSuggestionNodes.length == 1) {
                cur = 0;
            }
            else if (cSuggestionNodes.length > 0 && cur < cSuggestionNodes.length - 1) {
                ++cur;
            }
            if (oldCur != cur) {
                var oNode = cSuggestionNodes[cur];
                highlightSuggestion(oNode);
                setNewValue(oNode.firstChild.nodeValue);
            }
        }

        function previousSuggestion() {
            var cSuggestionNodes = that.container.childNodes,
                oldCur = cur;
            if (cSuggestionNodes.length == 1) {
                cur = 0;
            }
            else if (cSuggestionNodes.length > 0 && cur > 0) {
                --cur;
            }
            if (oldCur != cur) {
                var oNode = cSuggestionNodes[cur];
                highlightSuggestion(oNode);
                setNewValue(oNode.firstChild.nodeValue);
            }
        }

        function showSuggestions(aSuggestions /*:Array*/) {        
            var oDiv = null,
                width = inputBox.container.offsetWidth;
            that.container.innerHTML = "";

            for (var i = 0; i < aSuggestions.length; i++) {
                oDiv = that.add(new innovaphone.ui1.Div(config.suggestionStyle, aSuggestions[i], config.suggestionCl));
                oDiv.container.style.width = (width - 10) + "px";   // margin ...
                oDiv.container.style.paddingLeft = "5px";
                oDiv.container.style.paddingRight = "5px";
                oDiv.container.style.overflow = "hidden";
                oDiv.container.style.textOverflow = "ellipsis";
            }
            if (container.style.display == "flex") {    // otherwise ???
                that.container.style.marginTop = inputBox.container.getBoundingClientRect().height + "px";
            }
            that.container.style.width = width + "px";
            that.container.style.display = "block";
        }

        init();
    }
    AutoSuggestControl.prototype = innovaphone.ui1.nodePrototype;

    var oTextbox = this.add(new AutoSuggestControl(inputBox.container));
    
    this.setDataCallBack = function (dataCallBack) {
        callBackOnChange = dataCallBack;
    }

    this.setCompleteDataCallBack = function (callbackCompleteValue) {
        callBackCompleteValue = callbackCompleteValue;
    }

    this.triggerAutoComplete = function (cSuggestions) {
        oTextbox.handleSuggestion(cSuggestions);

    }

    this.inputBox = inputBox;
    this.style = inputBox.style;
    this.value = function () { return inputBox.container.value; };

    this.addEventListener = function (type, listener) {
        inputBox.container.addEventListener(type, listener);
    }

    this.focus = function () {
        inputBox.container.focus();
    }

    this.setValue = function (value) {
        if (value === null || value === undefined) return;
        inputBox.container.value = value;
    }

    this.setMaxLength = function (maxLength) {
        inputBox.container.maxLength = maxLength;
    }

    this.setWidth = function (width) {
        inputBox.container.style.width = (width - 4) + "px";
    }

    this.setPlaceHolder = function (placeHolder) {
        inputBox.container.placeholder = placeHolder;
    }

    this.setOnEnter = function (onEnter) {

        inputBox.container.setOnEnter(onEnter);
    }

    this.setOnChange = function (onChange) {
        inputBox.container.addEventListener("change", onChange);
    }

    this.hasChanged = function () {
        return inputBox.container.hasChanged();
    }

    this.enable = function () {
        inputBox.container.disabled = false;
    }

    this.disable = function () {
        inputBox.container.disabled = true;
    }

    this.isDisabled = function () {
        return inputBox.container.disabled;
    }

    this.setSeparator = function (separatorIn) {
        separator = separatorIn;

    }
    this.getLastValue = function () {
        return getCurrentValue();
    }

};

innovaphone.ui1.AutoCompleteInput.prototype = innovaphone.ui1.nodePrototype;
