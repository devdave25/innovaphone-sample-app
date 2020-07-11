
// login as user

function AppWebsocketLogin(addr, usr, pwd, out) {
    var ws = new WebSocket("ws://" + addr + "/PBX0/APPS/websocket");

    ws.onopen = function () {
        ws.send(JSON.stringify({ mt: "AppChallenge" }));
    }

    ws.onmessage = function (message) {
        var obj = JSON.parse(message.data);

        if (obj.mt && obj.mt == "AppChallengeResult") {
            var digest = innovaphone.common.crypto.sha256("::" + usr + ":::" + obj.challenge + ":" + pwd);
            ws.send(JSON.stringify({ mt: "AppLogin", sip: usr, digest: digest }));
        }
        else if (obj.mt && obj.mt == "AppLoginResult") {
            if (obj.ok) outp("login ok");
            else outp("login failed");
        }
    }

    ws.onerror = function () {
        outp("error");
    }

    ws.onclose = function () {
        outp("close");
    }

    function outp(text) {
        var div = document.createElement("div");
        div.innerHTML = text;
        out.appendChild(div);
    }
}