var innovaphone = innovaphone || {};
innovaphone.ui1 = innovaphone.ui1 || {};
innovaphone.ui1.RadioButton = innovaphone.ui1.RadioButton || function (style, groupName, elements, funcOnClick, defaultSelection, vertical, cl) {
    
    this.createNode("div", style, "", cl);
    var container = this.container;
    var _this = this;
    this.makeRadioButton = function (name, value, checked, vertical) {
        
        var labelControl = _this.add(new innovaphone.ui1.Node("label","" ,value));

        var label = labelControl.container;
        var radioControl = _this.add(new innovaphone.ui1.Node("input")); 
        var breakLine = null;
        var radio = radioControl.container;
        radio.type = "radio";
        radio.name = name;
        radio.value = value;
        radio.checked = checked;
        radio.addEventListener("click", _this.onclick);
        if (vertical)
            breakLine = _this.add(new innovaphone.ui1.Node("br"));
        return label;
    }

    this.getSelected = function () {
        var selection = document.querySelector('input[name = "' + _this.groupName + '"]:checked').value;
        return selection;
    };
    this.onclick = function () {
        var selection = _this.getSelected();
        if (_this.funcOnClick) {
            _this.funcOnClick(selection);
        }
    }

    this.funcOnClick = funcOnClick;
    
    this.groupName = groupName;
    for (var i = 0; i < elements.length; i++) {
        var checked = false;
        if (elements[i] == defaultSelection) {
            checked = true;
        }
        var newRadio = this.makeRadioButton(groupName, elements[i], checked, vertical || false);
    }


    this.addEvent("click", onclick);
    
};

innovaphone.ui1.RadioButton.prototype = innovaphone.ui1.nodePrototype;


