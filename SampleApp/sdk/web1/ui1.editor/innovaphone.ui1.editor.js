
/// <reference path="../lib1/innovaphone.lib1.js" />
/// <reference path="../ui1.lib/innovaphone.ui1.lib.js" />
/// <reference path="../ui1.scrolling/innovaphone.ui1.scrolling.js" />

var innovaphone = innovaphone || {};
innovaphone.ui1 = innovaphone.ui1 || {};
innovaphone.ui1.ListViewResources = innovaphone.ui1.ListViewResources || function (onload) {
    innovaphone.lib.loadObjectScripts(["web/ui1.scrolling/innovaphone.ui1.scrolling"], function () {
        innovaphone.ui1.ListViewResourcesLoaded = true;
        onload();
    });
};

innovaphone.ui1.Editor = innovaphone.ui1.Editor || function (style, scrollWidth, scrollColor, scrollStyle, onCtrlEnter, onEsc, onChanged, onFocus, onEmphasis) {
    var scrolling = new innovaphone.ui1.Scrolling(style, -1, 0, scrollWidth, scrollColor, scrollStyle);
    var content = scrolling.content;
    this.container = scrolling.container;
    this.content = content;

    content.container.contentEditable = true;
    content.container.style.outlineStyle = "none";
    if (onFocus) {
        content.addEvent("focus", function () { onFocus(true) });
        content.addEvent("blur", function () { onFocus(false) });
    }

    content.addEvent('keydown', onKeyDown);
    content.addEvent('keyup', onKeyUp);
    content.addEvent('mouseup', onMouseUp);
    content.addEvent('paste', function () { setTimeout(function () { normalize(content.container) }, 0) });
    if (onEmphasis) document.addEventListener('selectionchange', onSelectionChange);

    var ctrl = false;
    var shift = false;
    var alt = false;

    function onKeyDown(e) {

        switch (e.keyCode) {
            case 13:
                if (onCtrlEnter) {
                    if (onCtrlEnter(ctrl, empty(content.container))) {
                        e.preventDefault();
                        ctrl = false;
                        return;
                    }
                }
                enter();
                e.preventDefault();
                break;
            case 16:
                shift = true;
                return;
            case 17:
                ctrl = true;
                return;
            case 18:
                alt = true;
                return;
            case 27:
                if (onEsc) {
                    onEsc();
                }
                return;
        }
        if (onChanged) onChanged(e.keyCode, getSelection(), e);
    }

    function enter() {
        var sel = selection();

        console.log("Enter: " + sel.p[0].nodeName);
        if (sel.p[0].tagName == "DIV") {
            sel.p.shift();
            var n = document.createElement("P");
            if (!sel.p[0].tagName) {
                n.innerHTML = (sel.f.textContent && sel.f.textContent.length > sel.o) ? sel.f.textContent.slice(sel.o) : "<br/>";
                sel.p[0].textContent = sel.p[0].textContent.slice(0, sel.o);
                sel.p[0].parentNode.insertBefore(n, sel.p[0].nextSibling);
            }
            else {
                var s = split(sel.p, sel.o);
                if (s) n.appendChild(s); else n.innerHTML = "<br/>";
                sel.p[0].parentNode.insertBefore(n, sel.p[0].nextSibling);
            }
            if (sel.p[0].textContent == "") {
                var r = document.createElement("P");
                r.innerHTML = "<br/>";
                sel.p[0].parentNode.insertBefore(r, sel.p[0].nextSibling);
            }
            focus(n, sel.selection);
        }
        else if (sel.p[0].tagName == "P") {
            var n = document.createElement("P");
            var s = split(sel.p, sel.o);
            if (s) { n = s; if (empty(sel.p[0])) sel.p[0].innerHTML = "<br/>"; }
            else n.innerHTML = "<br/>";
            sel.p[0].parentNode.insertBefore(n, sel.p[0].nextSibling);
            focus(n, sel.selection);
        }
        else if (sel.p[0].tagName == "LI") {
            if (empty(sel.p[0])) {
                unindentli(sel.p);
                sel.selection.collapse(sel.f, sel.o);
            }
            else {
                var s = split(sel.p, sel.o);
                var n = document.createElement("LI");
                if (s) n = s; else n.innerHTML = "<br/>";
                sel.p[0].parentNode.insertBefore(n, sel.p[0].nextSibling);
                focus(n, sel.selection);
            }
        }
        else if (sel.p[0].tagName == "DT" || sel.p[0].tagName == "DD") {
            var s = split(sel.p, sel.o);
            if (empty(sel.p[0]) && sel.p[0].tagName == "DT") {
                unindentli(sel.p);
                sel.selection.collapse(sel.f, sel.o);
            }
            else {
                var n = document.createElement(empty(sel.p[0]) ? "DT" : "DD");
                if (s) n = s; else n.innerHTML = "<br/>";
                sel.p[0].parentNode.insertBefore(n, sel.p[0].nextSibling);
                if (empty(sel.p[0])) sel.p[0].parentNode.removeChild(sel.p[0]);
                focus(n, sel.selection);
            }
        }
    }

    function focus(n, s) {
        while (n.firstChild && n.firstChild.tagName && n.firstChild.tagName != "BR") {
            n = n.firstChild;
        }
        s.collapse(n, 0);
        n.scrollIntoView(false);
    }

    function onKeyUp(e) {
        switch (e.keyCode) {
            case 16:
                shift = false;
                break;
            case 17:
                ctrl = false;
                break;
            case 18:
                alt = false;
                break;
        }
    }

    function onMouseUp(e) {
        console.log("onMouseUp");
    }

    function onSelectionChange(e) {
        var selection = getSelection();
        if (content.container.contains(selection.focusNode)) {
            var p = emphasis(selection.focusNode);
            var b = false, i = false, u = false;
            for (var j = 0; j < p.length; j++) {
                switch (p[j].nodeName) {
                    case 'B': b = true; break;
                    case 'I': i = true; break;
                    case 'U': u = true; break;
                }
            }
            onEmphasis(b, i, u, p[0].tagName == "LI" ? p[0].parentNode.tagName : p[0].tagName);
        }
    }

    function normalize(node, parent, before) {
        if (!parent) parent = node;
        var n;
        for (n = node.firstChild; n; ) {
            var p = node;
            if (['B', 'I', 'U', 'P', 'UL', 'OL', 'DL', 'LI', 'DT', 'DD'].indexOf(n.nodeName) != -1) {
                p = document.createElement(n.nodeName);
                parent.insertBefore(p, parent == node ? n : before);
                before = null;
            }
            else if (n.nodeType == 3) {
                parent.insertBefore(document.createTextNode(n.textContent), parent == node ? n : before);
            }
            if (n.nodeType == 1) normalize(n, p, before);
            var d = n;
            n = n.nextSibling;
            node.removeChild(d);
        }
    }

    function emphasis(node, name) {
        var r = [];
        r.unshift(node);
        do {
            if (node.nodeName == name) break;
            node = node.parentNode;
            r.unshift(node);
        } while (['B', 'I', 'U'].indexOf(node.nodeName) != -1);
        return r;
    }

    function split(p, ofs) {
        console.log("split(" + p[0].tagName + ") " + p[0].innerHTML + " at " + ofs);
        var r = document.createElement(p[0].nodeName);
        var c = r;
        for (var j = 1; j < p.length; j++) {
            var i;
            if (p[j].nodeType == 3) {
                i = c.appendChild(document.createTextNode(p[j].textContent.slice(ofs)));
                p[j].textContent = p[j].textContent.slice(0, ofs);
            }
            else {
                i = c.appendChild(document.createElement(p[j].nodeName));
            }
            while (p[j].nextSibling) {
                c.appendChild(p[j - 1].removeChild(p[j].nextSibling));
            }
            c = i;
        }
        if (empty(r.firstChild)) r.removeChild(r.firstChild);
        console.log(p[0].innerHTML + " - " + (empty(r) ? "<empty>" : r.innerHTML));
        if (!empty(r)) return r;
        return null;
    }

    function empty(node, next) {
        if (node.nodeType == 3 && node.textContent.length) return false;
        if (node.firstChild) {
            if (!empty(node.firstChild, true)) return false;
        }
        if (next && node.nextSibling) {
            if (!empty(node.nextSibling, true)) return false;
        }
        return true;
    }

    function selection() {
        var s = {};
        s.selection = getSelection();
        s.f = s.selection.focusNode;
        if (!content.container.contains(s.f)) return null;
        s.o = s.selection.focusOffset;
        if (s.f.tagName) {
            if (s.f.tagName == "BR") {
                s.f = s.f.parentNode.insertBefore(document.createTextNode(""), s.f);
            }
            else {
                s.f = s.f.appendChild(document.createTextNode(""));
            }
            s.o = 0;
        }
        s.p = emphasis(s.f, "X");
        return s;
    }

    function list(p, tag) {
        var l = document.createElement(tag);
        p[0].insertBefore(l, p[1]);
        p[0].removeChild(p[1]);
        var li = document.createElement("LI");
        l.appendChild(li);
        li.appendChild(p[1]);
    }

    function listli(p, tag) {
        var r = p[0].parentNode;
        if (r.tagName == tag) {
            var n = r.nextSibling;
            while (p[0].firstChild) r.parentNode.insertBefore(p[0].removeChild(p[0].firstChild), n);
            if (p[0].nextSibling) {
                var t = r.parentNode.insertBefore(document.createElement(tag), n);
                while (p[0].nextSibling) t.appendChild(r.removeChild(p[0].nextSibling));
            }
            r.removeChild(p[0]);
        }
        else {
            var l = document.createElement(tag);
            while (r.firstChild) l.appendChild(r.removeChild(r.firstChild));
            r.parentNode.replaceChild(l, r);
        }
    }

    function dlist(p) {
        var dl = document.createElement("DL");
        p[0].insertBefore(dl, p[1]);
        p[0].removeChild(p[1]);
        var dt = document.createElement("DT");
        dl.appendChild(dt);
        dt.appendChild(p[1]);
        var dd = dl.appendChild(document.createElement("DD"));
        dd.innerHTML = "<br/>";
        return dd;
    }

    function dlistdt(p) {
        var r = p[0].parentNode;
        if (r.tagName == "DL") {
            var n = r.nextSibling;
            while (p[0].firstChild) r.parentNode.insertBefore(p[0].removeChild(p[0].firstChild), n);
            if (p[0].nextSibling) {
                var t = r.parentNode.insertBefore(document.createElement("DL"), n);
                while (p[0].nextSibling) t.appendChild(r.removeChild(p[0].nextSibling));
            }
            r.removeChild(p[0]);
        }
    }

    function indentli(p) {
        if (p[0].previousSibling) {
            var l = document.createElement(p[0].parentNode.tagName);
            p[0].previousSibling.appendChild(l);
            var li = l.appendChild(document.createElement("LI"));
            li.appendChild(p[1]);
            p[0].parentNode.removeChild(p[0]);
        }
    }

    function unindentli(p) {
        if (p[0].nextElementSibling) {
            var l = document.createElement(p[0].parentNode.tagName);
            p[0].parentNode.parentNode.insertBefore(l, p[0].parentNode.nextSibling);
            while (p[0].nextSibling) l.appendChild(p[0].nextSibling);
        }
        if (p[0].parentNode.parentNode.nodeName == "LI") {
            var li = p[0].parentNode.parentNode.parentNode.insertBefore(document.createElement("LI"), p[0].parentNode.parentNode.nextSibling);
            li.appendChild(p[1]);
            p[0].parentNode.removeChild(p[0]);
        }
        else {
            p[0].parentNode.parentNode.insertBefore(p[1], p[0].parentNode.nextSibling);
            p[0].parentNode.removeChild(p[0]);
        }
    }

    this.selection = function (tag) {
        var selection = getSelection();
        console.log("selection(" + tag + ")");
        var f = selection.focusNode;
        var o = selection.focusOffset;
        var p = emphasis(f, tag);
        if (selection.isCollapsed) {
            if (p[0].tagName != tag) {
                var node = document.createElement(tag);
                if (f.nodeType == 3) {
                    f.parentNode.insertBefore(node, f.nextSibling);
                    if (selection.focusOffset != f.textContent.length) {
                        f.parentNode.insertBefore(document.createTextNode(f.textContent.slice(selection.focusOffset)), node.nextSibling);
                        f.textContent = f.textContent.slice(0, o);
                    };
                }
                else {
                    f.insertBefore(node, f.firstChild);
                }
                selection.collapse(node, 0);
            }
            else {
                var s = split(p, o);
                var t = document.createTextNode("");
                var c;
                for (var j = 1; j < p.length; j++) {
                    if (p[j].nodeType != 3) {
                        var n = document.createElement(p[j].nodeName);
                        if (c) c.appendChild(n);
                        else p[0].parentNode.insertBefore(n, p[0].nextSibling);
                        c = n;
                    }
                }
                if (c) c.appendChild(t);
                else p[0].parentNode.insertBefore(t, p[0].nextSibling)
                if (s) p[0].parentNode.insertBefore(s, c ? p[0].nextSibling.nextSibling : t.nextSibling);
                selection.collapse(t, 0);
            }
        }
        else {
            var range = selection.getRangeAt(0);
            if (p[0].tagName != tag) {
                traverse(range.startContainer, range.endContainer, range.startOffset, range.endOffset, set);
            }
            else {
                traverse(range.startContainer, range.endContainer, range.startOffset, range.endOffset, unset);
            }
        }

        function traverse(start, end, sofs, eofs, op) {
            var c = 0;
            console.log("[traverse " + start.textContent + " (" + sofs + ")" + " -> " + end.textContent + " (" + eofs + ")");
            var cur = start;
            var up = false;
            var next;
            if (cur.nodeType == 3) {
                var p = emphasis(cur, tag);
                next = op(p, cur, sofs, start == end ? eofs : cur.textContent.length, tag);
            }
            while (cur != end) {
                if (c++ == 100) {
                    console.log("LOOP!");
                    return;
                }
                if (next) cur = next;
                next = null;
                if (cur.firstChild && !up) { console.log("down"); cur = cur.firstChild; }
                else if (cur.nextSibling) { console.log("next"); cur = cur.nextSibling; up = false }
                else { console.log("up"); cur = cur.parentNode; up = true; };
                console.log("cur ", cur.nodeName);
                if (cur.nodeType == 3 && cur.textContent.length) {
                    var p = emphasis(cur, tag);
                    next = op(p, cur, 0, cur == end ? eofs : cur.textContent.length, tag);
                    console.log("next ", next.nodeName);
                }
            }
            selection.collapse(content.container, 0);
            content.container.blur();
            console.log("traverse]");
        }

        function set(p, node, start, end, name) {
            console.log("set " + node.textContent + " (" + p[0].parentNode.innerHTML + ") " + p[0].nodeName + " " + start + "/" + end);
            if (p[0].nodeName != name) {
                if (start) {
                    node.parentNode.insertBefore(document.createTextNode(node.textContent.slice(0, start)), node);
                }
                var n = node.parentNode.insertBefore(document.createElement(name), node);
                n.appendChild(document.createTextNode(node.textContent.slice(start, end)));
                node.textContent = node.textContent.slice(end);
                console.log("ret " + p[0].parentNode.innerHTML + " next=" + node.innerHTML);
            }
            return node;
        }

        function unset(p, node, start, end, name) {
            console.log("unset " + node.textContent + " (" + p[0].parentNode.innerHTML + ") " + p[0].nodeName + " " + start + "/" + end);
            if (p[0].nodeName == name) {
                var t = document.createTextNode(node.textContent.slice(start, end));
                var ret = t;
                for (var i = p.length - 2; i; i--) {
                    var n = document.createElement(p[i].nodeName);
                    n.appendChild(t);
                    t = n;
                }
                if (empty(t)) t = null;

                var s = split(p, end);

                if (s) p[0].parentNode.insertBefore(s, p[0].nextSibling);
                if (t) p[0].parentNode.insertBefore(t, p[0].nextSibling);

                node.textContent = node.textContent.slice(0, start);
                console.log("ret " + p[0].parentNode.innerHTML + "next " + ret);
                if (empty(p[0])) p[0].parentNode.removeChild(p[0]);

                return t ? ret : s;
            }
            return node;
        }
    }

    this.l = function (tag) {
        var s = selection();
        if (!s) return;
        console.log("l(" + tag + ") f=" + s.f.nodeName + " p=" + s.p[0].nodeName + " " + (s.p[1] ? s.p[1].nodeName : "-"));
        if (s.p[0].tagName == "LI") {
            listli(s.p, tag);
        }
        else {
            list(s.p, tag);
        }
        s.selection.collapse(s.f, s.o);
        if (onChanged) onChanged();
    }

    this.dl = function () {
        var s = selection();
        if (!s) return;
        console.log("dl f=" + s.f.nodeName + " p=" + s.p[0].nodeName + " " + s.p[1].nodeName);
        if (s.p[0].tagName == "DT" || s.p[0].tagName == "DD") {
            dlistdt(s.p);
        }
        else {
            console.log("a");
            s.selection.collapse(dlist(s.p), 0);
        }
        if (onChanged) onChanged();
    }

    this.indent = function () {
        var s = selection();
        if (!s) return;
        console.log("indent f=" + s.f.nodeName + " p=" + s.p[0].nodeName + " " + s.p[1].nodeName);
        if (s.p[0].tagName == "LI") {
            indentli(s.p);
            s.selection.collapse(s.f, s.o);
        }
    }

    this.unIndent = function () {
        var s = selection();
        if (!s) return;
        console.log("unIndent f=" + s.f.nodeName + " p=" + s.p[0].nodeName + " " + s.p[1].nodeName);
        if (s.p[0].tagName == "LI") {
            unindentli(s.p);
            s.selection.collapse(s.f, s.o);
        }
    }

    this.insert = function (text) {
        var s = selection();
        if (s) s.f.textContent = s.f.textContent.slice(0, s.o) + text + s.f.textContent.slice(s.o);
        s.selection.collapse(s.f, s.o + text.length);
    }

    this.backspace = function (num) {
        var s = selection();
        if (s) s.f.textContent = s.f.textContent.slice(0, s.o - num) + s.f.textContent.slice(s.o);
        s.selection.collapse(s.f, s.o - num);
    }

    this.text = function (noempty) { return noempty && empty(content.container) ? null : content.container.innerHTML.replace(/<br>/g, "<br/>"); }
    this.setText = function (html) { content.addHTML(html); if (onChanged) onChanged() };
    this.focus = function () { content.container.focus(); }
    this.blur = function () { content.container.blur(); }
    this.contentHeight = function () { return scrolling.contentHeight(); };
};
innovaphone.ui1.Editor.prototype = innovaphone.ui1.nodePrototype;
