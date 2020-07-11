
function RCC(addr, app, pwd, out) {
    var ws = new WebSocket("ws://" + addr + "/PBX0/APPS/websocket");
    out.innerHTML = null;

    ws.onopen = function () {
        ws.send(JSON.stringify({ mt: "AppChallenge" }));
    }

    ws.onmessage = function (message) {
        var obj = JSON.parse(message.data);

        if (obj.mt && obj.mt == "AppChallengeResult") {
            var digest = innovaphone.common.crypto.sha256(app + ":::::" + obj.challenge + ":" + pwd);
            ws.send(JSON.stringify({ mt: "AppLogin", app: app, digest: digest }));
        }
        else if (obj.mt && obj.mt == "AppLoginResult") {
            if (obj.ok) outp("login ok");
            else outp("login failed");
            ws.send(JSON.stringify({ mt: "Initialize", api: "RCC" }));
        }
        else if (obj.mt && obj.mt == "InitializeResult") {
            outp("initialized");
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