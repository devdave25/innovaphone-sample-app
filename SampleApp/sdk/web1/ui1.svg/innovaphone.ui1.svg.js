
/// <reference path="../ui.lib1/innovaphone.ui1.lib.js" />

innovaphone = innovaphone || {};
innovaphone.ui1 = innovaphone.ui1 || {};
innovaphone.ui1.Svg = innovaphone.ui1.Svg || function (style, url, cl) {
    var svg = document.createElementNS("http://www.w3.org/2000/svg", "svg"),
    use = document.createElementNS("http://www.w3.org/2000/svg", "use");

    if (style) svg.setAttribute("style", style);
    if (cl) svg.setAttribute("class", cl);
    svg.setAttributeNS("http://www.w3.org/2000/xmlns/", "xmlns:xlink", "http://www.w3.org/1999/xlink");
    svg.appendChild(use);
    use.style.pointerEvents = "none";

    this.setUrl = function (value) {
        svg.removeChild(use);
        use = document.createElementNS("http://www.w3.org/2000/svg", "use");
        use.setAttributeNS("http://www.w3.org/1999/xlink", "xlink:href", value);
        svg.appendChild(use);
    }

    use.setAttributeNS("http://www.w3.org/1999/xlink", "xlink:href", url);
    this.container = svg;
}
innovaphone.ui1.Svg.prototype = innovaphone.ui1.nodePrototype;

innovaphone.ui1.SvgInline = innovaphone.ui1.SvgInline || function (style, viewbox, code, cl) {
    var svg = document.createElementNS("http://www.w3.org/2000/svg", "svg");
    if (style) svg.setAttribute("style", style);
    if (viewbox) svg.setAttribute("viewBox", viewbox);
    if (code) svg.innerHTML = code;
    if (cl) svg.setAttribute("class", cl);

    this.setCode = function (value) {
        svg.innerHTML = "" + value;
    }

    this.container = svg;
}
innovaphone.ui1.SvgInline.prototype = innovaphone.ui1.nodePrototype;
