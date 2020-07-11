/// <reference path="~/sdk/web1/lib1/innovaphone.lib1.js" />

var innovaphone = innovaphone || {};

innovaphone.Avatar = innovaphone.Avatar || function (start, user, domain, appdomain) {
    var api = start.consumeApi("com.innovaphone.avatar"),
        base = null,
        token = null,
        salt = null,
        providers = [];

    if (!appdomain) appdomain = domain;
    api.onupdate.attach(init);
    init();
    
    function init() {
        providers = [];
        for (var i = 0; i < api.providers.length; i++) {
            var model = api.model[api.providers[i]];
            providers.push({ base: model.url.slice(0, model.url.lastIndexOf("/") + 1) + model.info.filename, domain: model.info.domain, token: model.info.token, salt: innovaphone.crypto.randomString(16) });
        }
    }

    this.url = function (sip, size, dn) {
        if (!sip) sip = "";
        else if (sip == undefined) sip = "";
        var at = sip.indexOf("@");
        var d = appdomain;
        if (at != -1) {
            d = sip.slice(at + 1);
            sip = sip.slice(0, at);
        }
        var p = providers.find(function (p) { return p.domain == d });
        if (p) {
            return p.base + "?sip=" + sip + "&salt=" + p.salt + "&auth=" + encodeURIComponent(innovaphone.crypto.sha256(p.token + p.salt + sip)) + "&size=" + size + (dn ? ("&dn=" + encodeURIComponent(dn)) : "") + "&user=" + user + "&dom=@" + domain;
        }
        else {
            return "";
        }
    }
}
