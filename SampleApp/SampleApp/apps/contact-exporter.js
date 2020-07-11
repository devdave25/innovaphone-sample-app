
/// <reference path="../../sdk/web1/lib1/innovaphone.lib1.js" />
/// <reference path="../../sdk/web1/appwebsocket/innovaphone.appwebsocket.Connection.js" />
/// <reference path="../../sdk/web1/ui1.lib/innovaphone.ui1.lib.js" />
/// <reference path="../../sdk/web1/ui1.listview/innovaphone.ui1.listview.js" />

var reinforce = reinforce || {};
reinforce.ContactExporter = reinforce.ContactExporter || function (start, args) {
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

    var list = new innovaphone.ui1.Div("position: absolute; left:20px; top:100px; right:20px; height:300px", null, "");
    document.getElementById("out").appendChild(list.container);

    var contacts = [];
    var tempContacts = [];

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
                tempContacts.push(obj.msg.contact);
                contacts = [...new Set(tempContacts.map(o => JSON.stringify(o)))].map(s => JSON.parse(s));
                contactCounter.addHTML("" + contacts.length);
                console.log("contacts:", contacts);
                updateTable();
                break;
            case "SearchResult":
                break;
        }
    }

    function updateTable() {

        listView = new innovaphone.ui1.ListView(list, 30, "headercl", "arrow", false);

        var columns = contacts.length > 0 ? Object.keys(contacts[0]) : [];
        var rows = contacts.length;

        for (i = 0; i < columns.length; i++) {
            listView.addColumn(null, "text", columns[i], i, 40, false);
        }
        for (i = 0; i < rows; i++) {
            var row = [];
            for (j = 0; j < columns.length - 1; j++) {
                row.push("" + row[i][columns[j]]);
            }
            listView.addRow(i, row, "rowcl", "#A0A0A0", "#82CAE2");
        }
    }

    this.add(new innovaphone.ui1.Div("width: 80px", null, "button")).addTranslation(texts, "load").addEvent("click", function () {
        var alphabet = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"];
        for (var index in alphabet) {
            console.log("letter - ", alphabet[index]);
            ++searchId;
            curSearchId = "" + searchId;
            searchApi.send({ mt: "Search", type: "contact", search: alphabet[index] }, "*", curSearchId);
        }
    });


    this.add(new innovaphone.ui1.Div("left: 100px; width: 80px", null, "button")).addTranslation(texts, "export").addEvent("click", function () {
        app.sendSrc({ mt: "IncrementCount" }, function (msg) {
            counter.addHTML("" + msg.count);
        });
    });


    var app = new innovaphone.appwebsocket.Connection(start.url, start.name);

    app.checkBuild = true;
    app.onconnected = app_connected;
    app.onmessage = app_message;
    app.onerror = app_error;

    function app_connected(domain, user, dn, appdomain) {
        var src = new app.Src(update);
        src.send({ mt: "MonitorCount" });

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
}

reinforce.ContactExporter.prototype = innovaphone.ui1.nodePrototype;
