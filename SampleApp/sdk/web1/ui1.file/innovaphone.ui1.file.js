/// <reference path="../lib1/innovaphone.lib1.js" />
/// <reference path="../ui.lib1/innovaphone.ui1.lib.js" />

var innovaphone = innovaphone || {};
innovaphone.ui1 = innovaphone.ui1 || {};

innovaphone.ui1.File = innovaphone.ui1.File || function (style, content, cl, update, multiple, accept, path, color) {
    this.createNode("div", style, content, cl);
    if (path) this.add(new innovaphone.ui1.SvgInline("position:absolute; left:0px; top:1px; width:20px; height:20px; fill:" + color + "; cursor:pointer", "0 0 20 20", '<path d="' + path + '" style="fill-rule:evenodd"/>'));

    var inp = document.createElement('input');
    inp.type = 'file';
    inp.setAttribute('style', "position:absolute; top:0; left:0; opacity:0; box-sizing:border-box; width:100%; height:100%; cursor:pointer");
    if (multiple) inp.setAttribute('multiple', 'true');
    if (accept) inp.setAttribute('accept', accept);
    this.container.appendChild(inp);
    inp.addEventListener('change', selection, false);
    inp.addEventListener('click', resetFiles, false);

    function selection(ev) {
        update(ev.target.files);
    }

    function resetFiles(ev) {
        inp.value = "";
    }
}

innovaphone.ui1.File.prototype = innovaphone.ui1.nodePrototype;