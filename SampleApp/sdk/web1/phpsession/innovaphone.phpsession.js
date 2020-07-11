
var innovaphone = innovaphone || {};
innovaphone.PhpSession = innovaphone.PhpSession || function (url, app, appStart, params) {
    var instance = this,
        url = url,
        challenge,
        timer;

    window.addEventListener('message', onpostmessage);
    login();


    function login() {
        httpGet(url + "?mt=AppChallenge", onchallenge);
        timer = setTimeout(login, 10000);
    }

    function onchallenge(text) {
        var obj = JSON.parse(text);
        if (obj && obj.mt) {
            challenge = obj.challenge;
            if (obj.mt == "AppChallengeResult") {
                window.parent.postMessage(JSON.stringify({ mt: "getLogin", app: app, challenge: obj.challenge }), "*");
            }
        }
    }

    function onpostmessage(e) {
        var obj = JSON.parse(e.data);
        if (obj.mt && obj.mt == "Login") {
            console.log(app + ": AppLogin(" + obj.sip + "@" + obj.domain + ")");
            httpGet(url + "?mt=AppLogin&app=" + encodeURIComponent(obj.app) + "&domain=" + encodeURIComponent(obj.domain) + "&sip=" + encodeURIComponent(obj.sip) + "&guid=" + encodeURIComponent(obj.guid) + "&dn=" + encodeURIComponent(obj.dn) + (obj.info ? "&info=" + encodeURIComponent(JSON.stringify(obj.info)) : "") + "&digest=" + encodeURIComponent(obj.digest) + "&challenge=" + encodeURIComponent(challenge), onlogin);
        }
    }

    function onlogin(text) {
        var obj = JSON.parse(text);
        if (obj && obj.mt && obj.mt == "AppLoginResult" && obj.ok) {
            var u = location.href.substring(0, location.href.lastIndexOf("/") + 1);
            location.href = u + appStart + params;
            clearTimeout(timer);
        }
    }

    function httpGet(url, funcComplete, funcFailed) {
        var xmlReq = new window.XMLHttpRequest();
        if (xmlReq) {
            xmlReq.open("GET", url, funcComplete ? true : false);
            xmlReq.send(null);
            if (funcComplete) {
                xmlReq.onreadystatechange = function () {
                    if (this.readyState == 4) {
                        if (this.status == 200) {
                            funcComplete(this.responseText, this.responseXML);
                        }
                        else {
                            if (funcFailed) funcFailed(this);
                            else funcComplete("{}");
                        }
                    }
                }
            }
        }
        return xmlReq;
    }
};
