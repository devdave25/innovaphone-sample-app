
/// <reference path="../../sdk/web1/lib1/innovaphone.lib1.js" />
/// <reference path="../../sdk/web1/appwebsocket/innovaphone.appwebsocket.Connection.js" />
/// <reference path="../../sdk/web1/com.innovaphone.avatar/com.innovaphone.avatar.js" />
/// <reference path="../../sdk/web1/ui1.lib/innovaphone.ui1.lib.js" />

var reinforce = reinforce || {};
reinforce.SampleApp = reinforce.SampleApp || function (start, args) {
    //console.log("start:", Object.keys(start));
    //console.log("start:", JSON.stringify(start));

    this.createNode("body");
    var that = this;

    var colorSchemes = {
        dark: {
            "--bg": "#191919",
            "--button": "#303030",
            "--text-standard": "#f2f5f6",
        },
        light: {
            "--bg": "white",
            "--button": "#e0e0e0",
            "--text-standard": "#4a4a49",
        }
    };
    var schemes = new innovaphone.ui1.CssVariables(colorSchemes, start.scheme);
    start.onschemechanged.attach(function () { schemes.activate(start.scheme) });

    var texts = new innovaphone.lib1.Languages(reinforce.SampleAppTexts, start.lang);
    start.onlangchanged.attach(function () { texts.activate(start.lang) });

    var counter = this.add(new innovaphone.ui1.Div("position:absolute; left:0px; width:100%; top:calc(50% - 50px); font-size:100px; text-align:center", "-"));
    var contactCounter = this.add(new innovaphone.ui1.Div("position:absolute; left:0px; width:100%; top:calc(50% - 150px); font-size:100px; text-align:center", "-"));
    var app = new innovaphone.appwebsocket.Connection(start.url, start.name);
    console.log("app:", Object.keys(app));

    app.checkBuild = true;
    app.onconnected = app_connected;
    app.onmessage = app_message;
    app.onerror = app_error;

    var avatarApi;
    function app_connected(domain, user, dn, appdomain) {
        if (!avatarApi) avatarApi = new innovaphone.Avatar(start, user, domain, appdomain);

        var src = new app.Src(update);
        src.send({ mt: "MonitorCount" });

        that.add(new innovaphone.ui1.Div("top:250px", null, "button")).addTranslation(texts, "count").addEvent("click", function () {
            app.sendSrc({ mt: "IncrementCount" }, function (msg) {
                counter.addHTML("" + msg.count);
            });
        });


        that.add(new innovaphone.ui1.Div("top:310px", null, "button")).addTranslation(texts, "contact").addEvent("click", function () {
            //searchApi.send({ mt: "Search", type: "contact", search: "44" });

            //src2.send({ mt: "Search", type: "contact", search: "44" });
            
            //app.sendSrc({ mt: "ApiRequest", api: "com.innovaphone.search", msg: { "mt": "Search", "type": "contact", "search": "44" } }, function (msg) {
            //    console.log("msg:", msg);
            //});

            src.send({ mt: "GetAppLogin", api: "PbxAdminApi", challenge: "1234", app: user });
        });

        function update(msg) {
            console.log("update msg:", msg);
            if (msg.mt == "MonitorCountResult" || msg.mt == "UpdateCount") {
                counter.addHTML("" + msg.count);
            }
        }
    }

    function app_message(msg) {
        console.log("msg --- ", msg);
    }

    function app_error(error) {
        console.log("error --- ", error);
    }

    var contacts = [];

    var phoneApi = start.consumeApi("com.innovaphone.phone");
    var clientApi = start.consumeApi("com.innovaphone.client");
    var searchId = 0 | 0, curSearchId;
    var searchApi = start.consumeApi("com.innovaphone.search");
    searchApi.onmessage.attach(onsearchmessage);
    function onsearchmessage(consumer, obj) {
        var provider, relevance, src = obj.src || obj.msg.source;
        console.log("obj:", obj);
        switch (obj.msg.mt) {
            case "SearchInfo":
                //if (src == curSearchId) {
                //    provider = searchApi.model[obj.provider];
                //    relevance = obj.msg.relevance || (provider.model ? provider.model.relevance : null);
                //    //addResult(obj.msg.contact, obj.msg.dn, obj.msg.cn, provider.title, relevance, obj.msg.link);
                //    console.warn("contact:", obj.msg.contact);
                //}
                console.warn("contact:", obj.msg.contact);
                contacts.push(obj.msg.contact);
                var uniqueArray = [...new Set(contacts.map(o => JSON.stringify(o)))].map(s => JSON.parse(s));
                contactCounter.addHTML("" + uniqueArray.length);
                break;
            case "SearchResult":
                break;
        }
    }

    var sip;

    var input = this.add(new innovaphone.ui1.Input("margin: 5px; background-color: var(--button); color: var(--text-standard); font-size: 16px; border: none;"));
    var avatar = this.add(new innovaphone.ui1.Div("width: 150px; height: 150px; margin: 10px; background-size: cover;"));



    this.add(new innovaphone.ui1.Div("top:360px", null, "button")).addTranslation(texts, "search").addEvent("click", function () {
    var alphabet = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"];
    for (var index in alphabet) {
        console.log("letter - ", alphabet[index]);
        ++searchId;
        curSearchId = "" + searchId;
        searchApi.send({ mt: "Search", type: "contact", search: alphabet[index] }, "*", curSearchId);
    }
    });


    this.add(new innovaphone.ui1.Div("top:410px", null, "button")).addTranslation(texts, "export").addEvent("click", function () {
        var uniqueArray = [...new Set(contacts.map(o => JSON.stringify(o)))].map(s => JSON.parse(s));
        console.warn("contacts", JSON.stringify(uniqueArray));
        const replacer = (key, value) => value === null ? '' : value // specify how you want to handle null values here
        const header = Object.keys(uniqueArray[0])
        //let csv = uniqueArray.map(row => header.map(fieldName => JSON.stringify(row[fieldName], replacer)).join(','));
        let csv = uniqueArray.map(row => header.map(fieldName => row[fieldName] === null ? '' : row[fieldName]).join(','));
        csv.unshift(header.join(','))
        csv = csv.join('\r\n')

        console.warn("csv", csv);


        var element = document.createElement('a');
        element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(text));
        element.setAttribute('download', filename);

        element.style.display = 'none';
        document.body.appendChild(element);

        element.click();

        document.body.removeChild(element);
    });


    input.addEvent("change", function () {
        if (sip) clientApi.send({ mt: "UnsubscribePresence", sip: sip });
        sip = input.getValue();
        avatar.container.style.backgroundImage = "url('" + avatarApi.url(sip, 150, sip) + "')";
        clientApi.send({ mt: "SubscribePresence", sip: sip });
    });

    avatar.addEvent("click", function () {
        if (sip) phoneApi.send({ mt: "StartCall", sip: sip });
    });

    var presenceColors = { "": "#badb8c", "away": "#ffd063", "busy": "#ff918f", "dnd": "#cb8cdb" };

    clientApi.onmessage.attach(function (sender, obj) {
        if (obj.msg.mt == "PresenceUpdated" && obj.msg.sip == sip) {
            avatar.container.style.borderRight = "10px solid " + presenceColors[obj.msg.presence[0].activity];
        }
    });
}

reinforce.SampleApp.prototype = innovaphone.ui1.nodePrototype;
