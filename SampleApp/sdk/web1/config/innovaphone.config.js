/*---------------------------------------------------------------------------*/
/* innovaphone.config.js                                                     */
/* A config library                                                          */
/*---------------------------------------------------------------------------*/

var innovaphone = innovaphone || {};
innovaphone.Config = innovaphone.Config || function() {
    var that = this,
        appWebsocket = null,
        initialized = false,
        itemInfos = [],
        evOnConfigItemsReceived = new innovaphone.lib1.Event(this),
        evOnConfigLoaded = new innovaphone.lib1.Event(this),
        evOnConfigUpdate = new innovaphone.lib1.Event(this),
        evOnConfigSaveResult = new innovaphone.lib1.Event(this);

    function init(app)
    {
        appWebsocket = new app.Src();
        appWebsocket.onmessage = this.onmessage;
        //appWebsocket = app;
        //srcID = app.Src;
        //appWebsocket.registerApi(that, "Config");
        appWebsocket.send({
            "api": "Config",
            "mt": "GetConfigItems"
        });
        //appWebsocket.send({
        //    "api": "Config",
        //    "src": srcID,
        //    "mt": "GetConfigItems"
        //});
    }

    this.onmessage = function (message)
    {
        switch (message.mt) {
            case "GetConfigItemsResult": recvConfigItems(message); break;
            case "ReadConfigResult": recvConfigValues(message, false); break;
            case "WriteConfigResult": if (message.src == appWebsocket.src) evOnConfigSaveResult.notify(message.result == "ok"); break;
            case "ConfigUpdate": recvConfigValues(message, true); break;
        }
    }

    function recvConfigItems(message)
    {
        if (message.src != appWebsocket.src) return;

        for (var i = 0; i < message.ConfigItems.length; ++i) {
            var obj = message.ConfigItems[i];
            console.log(message.ConfigItems[i].name);

            itemInfos[obj.name] = obj;
            switch (obj.type) {
                case "CHOICE":
                case "INT":
                case "DWORD":
                case "LONG64":
                case "ULONG64":
                    if ('minVal' in obj || 'maxVal' in obj) addLimitedProperty(obj, 0);
                    else addNumberProperty(obj, 0);
                    break;

                case "BOOL":
                    that[obj.name] = false;
                    break;

                case "STRING":
                    if (obj.password == true) addPasswordProperty(obj)
                    else that[obj.name] = "";
                    break;
            }
        }

        evOnConfigItemsReceived.notify();
        appWebsocket.send({ "api": "Config", "mt": "ReadConfig" });
    }

    function addPasswordProperty(obj)
    {
        obj.changed = false;
        Object.defineProperty(that, obj.name, {
            configurable: true,
            get()  { return obj.value; },
            set(v) { 
                if (obj.value != v) {
                    obj.value = v;
                    obj.changed = true;
                }
            }
        });
    }

    function addLimitedProperty(obj, defValue)
    {
        obj["value"] = defValue;
        Object.defineProperty(that, obj.name, {
            configurable: true,
            get()  { return obj.value; },
            set(v) {
                v = parseInt(v);
                if (isNaN(v)) console.log("Tried to set a NaN value to Config property " + obj.name );
                else {
                    if ('minVal' in obj && v < obj.minVal) v = obj.minVal;
                    else if ('maxVal' in obj && v > obj.maxVal) v = obj.maxVal;
                    obj.value = v;
                }
            }
        });
    }

    function addNumberProperty(obj, defValue)
    {
        obj["value"] = defValue;
        Object.defineProperty(that, obj.name, {
            configurable: true,
            get()  { return obj.value; },
            set(v) {
                v = parseInt(v);
                if (isNaN(v)) console.log("Tried to set a NaN value to Config property " + obj.name );
                else obj.value = v;
            }
        });
    }

    function recvConfigValues(message, configUpdate)
    {
        if (configUpdate == false && message.src != appWebsocket.src) return;

        var items = Object.keys(message.ConfigItems);
        for (var i = 0; i < items.length; ++i) {
            that[items[i]] = message.ConfigItems[items[i]];
        }

        initialized = true;

        if (configUpdate) evOnConfigUpdate.notify();
        else evOnConfigLoaded.notify();
    }

    function save()
    {
        var data = {};
        var names = Object.keys(itemInfos);
        for (var i = 0; i < names.length; ++i) {
            var curItem = itemInfos[names[i]];
            if (curItem.password == true) {
                if (curItem.changed == true) {
                    if (that[curItem.name] != "") {
                        var seed = Math.random().toString(36);
                        data[curItem.name] = { value: appWebsocket.encrypt(seed, that[curItem.name]), key: seed };
                    }
                }
            }
            else data[curItem.name] = that[curItem.name];
        }

        console.log("Data = " + JSON.stringify(data));
        appWebsocket.send({
            "api": "Config",
            "mt": "WriteConfig",
            "ConfigItems": data });
    }

    function getItemChoices(itemName)
    {
        var result = itemInfos[itemName];
        return result == null ? null : result.choices;
    }

    this.evOnConfigItemsReceived = evOnConfigItemsReceived;
    this.evOnConfigLoaded = evOnConfigLoaded;
    this.evOnConfigUpdate = evOnConfigUpdate;
    this.evOnConfigSaveResult = evOnConfigSaveResult;
    this.save = save;
    this.getItemChoices = getItemChoices;
    this.initialized = initialized;
    this.init = init;
};
