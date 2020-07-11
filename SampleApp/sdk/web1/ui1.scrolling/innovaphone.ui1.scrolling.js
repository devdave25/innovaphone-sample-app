
/// <reference path="../ui1.lib/innovaphone.ui1.lib.js" />

innovaphone = innovaphone || {};
innovaphone.ui1 = innovaphone.ui1 || {};
innovaphone.ui1.Scrolling = innovaphone.ui1.Scrolling || function (style, mx, my, width, color, cstyle, cl) {
    var init = true;
    this.createNode("div", style, null, cl);
    var that = this;
    if (navigator.platform.startsWith("Win") && !innovaphone.ui1.lib.browser.webkit) {
        var bars = this.container;
        if (!width) width = 8;
        if (!color) color = "red";
        if (!mx) mx = 0;
        if (!my) my = 0;
        //console.log("mx=" + mx + " my=" + my);

        var vb = this.add(new innovaphone.ui1.Div("position:absolute; top:0px; bottom:" + width + "px; right:0px; width:" + width + "px; overflow:hidden"));
        var v = vb.add(new innovaphone.ui1.Div("position:absolute; width:100%; background-color:" + color));

        var hb = this.add(new innovaphone.ui1.Div("position:absolute; left:0px; right:" + width + "px; bottom:0px; height:" + width + "px; overflow:hidden"));
        var h = hb.add(new innovaphone.ui1.Div("position:absolute; height:100%; background-color:" + color));

        var outer = this.add(new innovaphone.ui1.Div("position:absolute; left:0px; right:" + width + "px; top:0px; bottom:" + width + "px; overflow:hidden"));
        var inner = outer.add(new innovaphone.ui1.Div("position:absolute; overflow:scroll; -webkit-overflow-scrolling: touch; -moz-overflow-scrolling: touch; overflow-scrolling: touch; left:0px; right:-20px; top:0px; bottom:-20px"));
        var sizer = inner.add(new innovaphone.ui1.Div("position:absolute; display:inline-block;" + (mx == -1 ? "left:0px; right:0px;" : "") + (my == -1 ? "top:0px; bottom:0px;" : "")));

        new SizeListener(sizer, resize);
        new SizeListener(outer, resize);

        var content = new innovaphone.ui1.Div(cstyle);
        content.container.style.boxSizing = "border-box";
        sizer.container.appendChild(content.container);

        inner.container.addEventListener("scroll", onScroll);
        this.content = content;
        this.add = function (node, before) { return content.add(node, before); };
        this.rem = function (node) { content.rem(node); };
        this.clear = function () { content.clear(); };
        this.firstChild = function () { return content.firstChild(); };
        this.onScroll = null;
        this.setScrollTop = function (top) { inner.container.scrollTop = top; }
        this.getScrollTop = function () { return inner.container.scrollTop; }
        this.setScrollBottom = function (bottom) { inner.container.scrollTop = sizer.container.offsetHeight - outer.container.offsetHeight - bottom };
        this.getScrollBottom = function () { return sizer.container.offsetHeight - outer.container.offsetHeight - inner.container.scrollTop };
        this.scrollToBottom = function () { if (sizer.container.offsetHeight > outer.container.offsetHeight) inner.container.scrollTop = sizer.container.offsetHeight - outer.container.offsetHeight; };
        this.isScrollBottom = function () { return (inner.container.scrollTop >= (sizer.container.offsetHeight - outer.container.offsetHeight)); };
        this.isScrollTop = function () { return (inner.container.scrollTop == 0); };
        this.contentHeight = function () { return sizer.container.offsetHeight; };
        this.scrollIntoView = function (node, scrollIntoViewOptions) {
            var e = node.container || node;
            if (content.container.style.position == "relative") {
                inner.container.scrollTop = e.offsetTop;
            }
            else {
                inner.container.scrollTop = e.offsetTop - inner.container.offsetTop;
            }
        }
    }
    else {
        if (!mx) mx = 0;
        if (!my) my = 0;

        this.container.addEventListener("scroll", onScrollX);
        this.container.style.overflowX = mx == -1 ? "hidden" : "auto";
        this.container.style.overflowY = my == -1 ? "hidden" : "auto";
        this.container.style.overflowScrolling = this.container.style.WebkitOverflowScrolling = "touch";
        var content = this.add(new innovaphone.ui1.Div(cstyle));

        content.container.style.boxSizing = "border-box";

        this.content = content;
        this.add = function (node, before) { return content.add(node, before); };
        this.rem = function (node) { content.rem(node); };
        this.clear = function () { content.clear(); };
        this.firstChild = function () { return content.firstChild(); };
        this.onScroll = null;
        this.setScrollTop = function (top) { this.container.scrollTop = top; }
        this.getScrollTop = function () { return this.container.scrollTop; }
        this.setScrollBottom = function (bottom) { this.container.scrollTop = content.container.offsetHeight - this.container.clientHeight - bottom };
        this.getScrollBottom = function () { return content.container.offsetHeight - this.container.clientHeight - this.container.scrollTop };
        this.scrollToBottom = function () { if (content.container.offsetHeight > this.container.offsetHeight) this.container.scrollTop = content.container.offsetHeight - this.container.clientHeight; };
        this.isScrollBottom = function () {  return (this.container.scrollTop >= (content.container.offsetHeight - this.container.clientHeight)); };
        this.isScrollTop = function () { return (this.container.scrollTop == 0); };
        this.contentHeight = function () { return content.container.offsetHeight; };
        this.scrollIntoView = function (node, scrollIntoViewOptions) {
            var e = node.container || node;
            e.scrollIntoView(scrollIntoViewOptions);
        }
        
    }

    function onScrollX() {
        if (that.onScroll) that.onScroll();
    }

    function onScroll() {
        resize();
        if (that.onScroll) that.onScroll();
    }

    function resize() {
        //console.log("resize innerScroll=" + inner.container.scrollWidth + "x" + inner.container.scrollHeight + " inner=" + inner.container.offsetWidth + "x" + inner.container.offsetHeight + " outer=" + outer.container.offsetWidth + "x" + outer.container.offsetHeight + " content=" + content.container.offsetWidth + "x" + content.container.offsetHeight + " inner.Client=" + inner.container.clientWidth + "x" + inner.container.clientHeight + " bars=" + bars.offsetWidth + "x" + bars.offsetHeight);
        var x = sizer.container.offsetWidth ? sizer.container.offsetWidth : inner.container.scrollWidth;
        var y = sizer.container.offsetHeight ? sizer.container.offsetHeight : inner.container.scrollHeight;
        //console.log("sizer=" + sizer.container.offsetWidth + "x" + sizer.container.offsetHeight + " x=" + x + " y=" + y);
        //if (!bars.offsetWidth || !bars.offsetHeight) return;
        if (content.container.offsetWidth && content.container.offsetWidth > x) x = content.container.offsetWidth;
        if (content.container.offsetHeight && content.container.offsetHeight > y) y = content.container.offsetHeight;
        if (my > 0) bars.style.height = Math.min(y + (x > mx ? width : 0), my) + "px";
        if (mx > 0) bars.style.width = Math.min(x + (y > my ? width : 0), mx) + "px";
        if (init) {
            init = false;
            var iw = inner.container.clientWidth - bars.clientWidth + width - 20;
            var ih = inner.container.clientHeight - bars.clientHeight + width - 20;
            iw = Math.min(iw, ih);
            //console.log("init " + iw);
            inner.container.style.right = iw + "px";
            inner.container.style.bottom = iw + "px";
        }
        //console.log("sizing: innerScroll=" + inner.scrollWidth + "x" + inner.scrollHeight + " inner=" + inner.offsetWidth + "x" + inner.offsetHeight + " outer=" + outer.offsetWidth + "x" + outer.offsetHeight + " div=" + div.container.offsetWidth + "x" + div.container.offsetHeight + " inner.Client=" + inner.clientWidth + "x" + inner.clientHeight + " bars=" + bars.offsetWidth + "x" + bars.offsetHeight);
        var sy = x > bars.offsetWidth ? bars.offsetHeight - width : bars.offsetHeight;
        var sx = y > bars.offsetHeight ? bars.offsetWidth - width : bars.offsetWidth;
        //console.log("space=" + sx + "x" + sy);

        var vs = (sy + 1) / y * 100; // hack: add 1 to sx/sy to adjust to firefox miscalculation
        var hs = (sx + 1) / x * 100;
        //console.log("vs=" + sy + "/" + y + "=" + vs +" hs=" + sx + "/" + x + "=" + hs + " scrollLeft=" + inner.scrollLeft);
        var vo = inner.container.scrollTop / y * 100;
        var ho = inner.container.scrollLeft / x * 100;

        if (vs >= 100 || my < 0) {
            vs = 0;
            outer.container.style.right = "0px";
            hb.container.style.right = "0px";
        }
        else {
            outer.container.style.right = width + "px";
            hb.container.style.right = width + "px";
        }
        v.container.style.height = vs + "%";
        v.container.style.top = vo + "%";

        if (hs >= 100 || mx < 0) {
            hs = 0;
            outer.container.style.bottom = "0px";
            vb.container.style.bottom = "0px";
        }
        else {
            outer.container.style.bottom = width + "px";
            vb.container.style.bottom = width + "px";
        }
        h.container.style.width = hs + "%";
        h.container.style.left = ho + "%";
    }

    function SizeListener(node, onresize) {
        var obj = document.createElement('object');
        obj.setAttribute('style', 'display: block; position: absolute; top: 0; left: 0; height: 100%; width: 100%; overflow: hidden; pointer-events: none; z-index: -1;');
        obj.onload = onload;
        obj.type = 'text/html';
        obj.data = 'about:blank';
        obj.tabIndex = '-1';
        node.container.appendChild(obj);

        function onload(e) {
            this.contentDocument.defaultView.addEventListener('resize', onresize);
            onresize();
            onresize();
        }
    }
}

innovaphone.ui1.Scrolling.prototype = innovaphone.ui1.nodePrototype;