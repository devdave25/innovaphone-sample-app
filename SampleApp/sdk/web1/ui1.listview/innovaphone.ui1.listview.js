
/// <reference path="../ui.lib1/innovaphone.ui1.lib.js" />

innovaphone = innovaphone || {};
innovaphone.ui1 = innovaphone.ui1 || {};
innovaphone.ui1.ListView = innovaphone.ui1.ListView || function (out, rowHeight, headercl, arrowcl, vertical) {
    var cols = 0;
    var rows = 0;
    var dragging = null;
    var theader;
    var header;
    var table;
    this.cols = cols;
    this.rows = rows;
    
    if (vertical) {
        theader = out.add(new innovaphone.ui1.Node("table", "position:absolute; top:0px; width: 50%; height:100%; left:0px;", null, "table"));
        header = theader.add(new innovaphone.ui1.Node("tr", "position:absolute; top:0px; right: 0px; left:0px;", null, "headercl"));
        table = out.add(new innovaphone.ui1.Node("table", "position:absolute; top:0px; width: 50%; height: 100%; left:50%;", null, "table"));
    }
    else {
        theader = out.add(new innovaphone.ui1.Node("table", "position:relative; top:0px; width: 100%; height:" + rowHeight + "px; left:0px;", null, "table"));
        header = theader.add(new innovaphone.ui1.Node("tr", "position:absolute; top:0px; right: 0px; height:100%; left:0px;", null, "headercl"));
        table = out.add(new innovaphone.ui1.Node("table", "position:relative; top:0px; width: 100%; left:0px;", null, "table"));
    }
    var sortArrow = new innovaphone.ui1.Node("img", null, null, arrowcl);
    sortArrow.container.src = "arrow.png";

    this.addColumn = function (cl, contentcl, content, id, minWidth, int) {
        if (vertical) {
            var headerF = header.add(new innovaphone.ui1.Node("tr", "position:absolute; top:" + cols * rowHeight + "px; height:" + rowHeight + "px; left:0px;  right: 0px; display:block;", null, cl));
            var headerL = headerF.add(new innovaphone.ui1.Node("div", "display: inline-block;", content, contentcl));
            headerF.container.setAttribute("asc", true);
            headerF.container.setAttribute("col", cols);
            headerF.container.setAttribute("show", true);
            headerF.container.setAttribute("id", id);
            headerF.container.setAttribute("int", int);
            headerL.addEvent("mousedown", sortTableVertical, headerF, id);
            cols = cols + 1;
            header.container.style.height = cols * rowHeight+"px";            
        }
        else {
            var headerF = header.add(new innovaphone.ui1.Node("td", "position:absolute;", null, cl));
            var headerL = headerF.add(new innovaphone.ui1.Node("div", "display: inline-block", content, contentcl));
            var divId = headerF.add(new innovaphone.ui1.Div("position:absolute; width:10%; height:100%; top:0px; left:90%; background-color:transparent;", null, null));
            divId.addEvent("mousedown", mouseDown, id);
            divId.addEvent("mouseover", function () { document.body.style.cursor = "col-resize"; });
            header.addEvent("mouseout", function () { document.body.style.cursor = "default"; });
            headerF.container.setAttribute("asc", true);
            headerF.container.setAttribute("col", cols);
            headerF.container.setAttribute("show", true);
            headerF.container.setAttribute("id", id);
            headerF.container.setAttribute("int", int);
            headerL.addEvent("mousedown", sortTable, headerF, id);
            cols = cols + 1;
            var w = 100 / cols;
            var left = 0;
            for (var i = 0; i < theader.container.childNodes[0].childNodes.length; i++) {
                theader.container.childNodes[0].childNodes[i].style.display = "block";
                theader.container.childNodes[0].childNodes[i].style.width = w + "%";
                theader.container.childNodes[0].childNodes[i].style.left = left + "%";
                /*theader.container.childNodes[0].childNodes[i].style.height = rowHeight + "px";*/
                left = left + w;
            }            

            var start, x;
            function mouseDown(event, obj) {
                start = event.pageX;
                console.log("start: " + start);
                document.body.style.cursor = "col-resize";
                for (var i = 0; i < cols; i++) {
                    if (theader.container.childNodes[0].childNodes[i].id == obj) {
                        dragging = theader.container.childNodes[0].childNodes[i];
                        break;
                    }
                }
                header.addEvent("mousemove", mouseMove, obj);
                header.addEvent("mouseup", mouseUp, obj);
            }
            function mouseMove(event) {
                if (dragging != null) {
                    x = event.pageX - start;
                    console.log("x: " + x);
                    var h = dragging;
                    console.log("left: " + h.clientWidth + " twidth: " + theader.container.clientWidth);
                    if (h.clientWidth + x < theader.container.clientWidth) {
                        var next = h.nextElementSibling;
                        var found = false;
                        while (!found) {
                            //check if the next column is being shown or not
                            if (next.attributes[3].value == "false") {
                                next = next.nextElementSibling;
                                found = false;
                            }
                            else {
                                found = true;
                            }
                        }
                        found = false
                        var nextNext = next.nextElementSibling;
                        while (!found) {
                            if (nextNext == null) break;
                            if (nextNext.attributes[3].value == "false") {
                                nextNext = nextNext.nextElementSibling;
                                found = false;
                            }
                            else {
                                found = true;
                            }
                        }
                        var width = 100 / h.clientWidth;
                        if (nextNext == null) {
                            if ((h.clientWidth > minWidth && x < 0) || (x > 0 && next.clientWidth > minWidth)) {
                                var propX = (x / 80) * 100 / h.clientWidth;
                                var hw = parseFloat(h.style.width.substring(0, h.style.width.length - 1));
                                var nw = parseFloat(next.style.width.substring(0, next.style.width.length - 1));
                                var nl = parseFloat(next.style.left.substring(0, next.style.left.length - 1));
                                h.style.width = parseFloat(hw + propX) + "%";
                                next.style.width = parseFloat(nw - propX) + "%";
                                next.style.left = parseFloat(nl + propX) + "%";
                            }
                        }
                        else {
                            //set min column width = minWidth
                            if ((x < 0 && h.clientWidth > minWidth) || (x > 0 && next.offsetLeft < nextNext.offsetLeft - minWidth)) {
                                var propX = (x / 80) * 100 / h.clientWidth;
                                //console.log(propX);
                                //console.log(h.style.width + " " + next.style.width + " " + next.style.left);
                                var hw = parseFloat(h.style.width.substring(0, h.style.width.length - 1));
                                var nw = parseFloat(next.style.width.substring(0, next.style.width.length - 1));
                                var nl = parseFloat(next.style.left.substring(0, next.style.left.length - 1));
                                h.style.width = parseFloat(hw + propX) + "%";
                                next.style.width = parseFloat(nw - propX) + "%";
                                next.style.left = parseFloat(nl + propX) + "%";
                                //console.log(h.style.width + " " + next.style.width + " " + next.style.left);
                            }
                        }

                        for (var i = 0; i < theader.container.childNodes[0].childNodes.length; i++) {
                            for (var j = 0; j < table.container.childNodes.length; j++) {
                                table.container.childNodes[j].childNodes[i].style.width = theader.container.childNodes[0].childNodes[i].style.width;
                                table.container.childNodes[j].childNodes[i].style.left = theader.container.childNodes[0].childNodes[i].style.left;
                            }
                        }
                    }
                }

            }
            function mouseUp(event) {
                dragging = null;
                console.log("dragging null");
                header.remEvent("mousemove", mouseMove);
                header.remEvent("mouseup", mouseUp);
            }
        }
        this.cols = cols;
    }
    this.addRow = function (id, elements, cl, overColor, selectedColor, hidenData, clField) {
        var row;
        if (vertical) {
            var top = rows * cols * rowHeight;
            if (rows > 0) {
                var hd = theader.container.childNodes[0].cloneNode(true);
                var hd2 = theader.container.insertBefore(hd,null);
                hd2.style.top = top + "px";
            }
            row = table.add(new innovaphone.ui1.Node("tr", "position:absolute; top:" + top + "px; left:0px; height:" + cols * rowHeight + "px; right: 0px;", null, cl));
            row.container.id = id;
            row.container.hidenData = hidenData;
            rows = rows + 1;
            var rtop = 0;
            for (var i = 0; i < cols; i++) {
                var rowField = row.add(new innovaphone.ui1.Node("tr", "position:absolute; width:100%; left:0px; top:" + rtop + "px; height:" + rowHeight + "px; display:block", null, clField));
                rowField.add(new innovaphone.ui1.Div("display: inline-block", elements[i]));
                rowField.container.setAttribute("id", elements[i]);
                rtop = rtop + rowHeight;
            }
            table.container.style.height =  rows * cols * rowHeight +"px";
            resize();
        }
        else {
            var top = rows * rowHeight;
            rows = rows + 1;
            row = table.add(new innovaphone.ui1.Node("tr", "top:" + top + "px; left:0px; height:" + rowHeight + "px; width: 100%;", null, cl));
            row.container.id = id;
            row.container.hidenData = hidenData;
            var width = 100 / cols;
            var left = 0;           
            for (var i = 0; i < cols; i++) {
                //var width = theader.container.childNodes[0].childNodes[i].attributes[6].value;
                //if (width == 0) width = 100 / cols;
                if (!width[i] > 0) width[i] = 0;
                var rowField = row.add(new innovaphone.ui1.Node("td", "position:absolute; left:" + left + "%; display:block", null, clField));
                rowField.add(new innovaphone.ui1.Div("display: inline-block", elements[i]));
                rowField.container.setAttribute("id", elements[i]);
                left = left + width;
            }
            resize();
        }
        row.container.setAttribute("selected", false);
        row.container.addEventListener("click", function () {
            if (row.container.selected) {
                row.container.selected = false;
                row.container.style.backgroundColor = "";
            }
            else {
                row.container.selected = true;
                row.container.style.backgroundColor = selectedColor;
            }
        });
        row.container.addEventListener("mouseover", function () { if (!row.container.selected) row.container.style.backgroundColor = overColor; });
        row.container.addEventListener("mouseout", function () { if (!row.container.selected) row.container.style.backgroundColor = ""; });
        this.rows = rows;
    }

    this.rowAddEvent = function (rowNum, type, func, obj) {
        table.container.childNodes[rowNum].addEventListener(type, func, obj);
    }

    this.getHeight = function () {
        return rowHeight*(rows);
    }

    this.getSelectedRows = function () {
        var selectedRows = [];
        var count = 0;
        for (var i = 0; i < table.container.rows.length; i++) {
            var row = table.container.rows[i];
            if (row.selected) {
                selectedRows[count] = i;
                count++;
            }
        }
        return selectedRows;
    }

    this.getRowData = function (id) {
        var data = [];
        for (var i = 0; i < cols; i++) {
            data[i] = table.container.rows[id].childNodes[i].id;
        }
        return data;
    }

    this.removeRow = function (num) {
        var top = table.container.childNodes[num].offsetTop;
        table.container.deleteRow(num);
        if (vertical && rows > 1) theader.container.deleteRow(num);
        rows = table.container.childNodes.length;
        for (var i = num; i < rows; i++) {
            table.container.childNodes[i].style.top = top + "px";
            if (vertical) {
                theader.container.childNodes[i].style.top = top + "px";
                top = top + rowHeight * cols;
            }
            else {
                top = top + rowHeight;
            }            
        }
        if (vertical && rows) resize();
        this.rows = rows;
    }

    this.removeRowById = function (id) {
        var num = 0;
        for (var r = 0; r < rows; r++) {
            if (table.container.childNodes[r].id == id) {
                num = id;
                break;
            }
        }
        var top = table.container.childNodes[num].offsetTop;
        table.container.deleteRow(num);
        if (vertical && rows > 1) theader.container.deleteRow(num);
        rows = table.container.childNodes.length;
        for (var i = num; i < rows; i++) {
            table.container.childNodes[i].style.top = top + "px";
            if (vertical) {
                theader.container.childNodes[i].style.top = top + "px";
                top = top + rowHeight * cols;
            }
            else {
                top = top + rowHeight;
            }
        }
        if (vertical && rows) resize();
        this.rows = rows;
    }

    this.removeColumn = function (num) {
        if (vertical) {
            for (var j = 0; j < rows; j++) {
                theader.container.childNodes[j].removeChild(theader.container.childNodes[j].childNodes[num]);
                table.container.childNodes[j].removeChild(table.container.childNodes[j].childNodes[num]);
            }
            cols = theader.container.childNodes[0].childNodes.length;
            for (var i = 0; i < table.container.childNodes.length; i++) {
                theader.container.childNodes[i].style.display = "block";
                theader.container.childNodes[i].style.top = i * rowHeight * cols + "px";
                theader.container.childNodes[i].style.height = rowHeight * cols + "px";
                table.container.childNodes[i].style.display = "block";
                table.container.childNodes[i].style.top = i * rowHeight * cols + "px";
                table.container.childNodes[i].style.height = rowHeight * cols + "px";
                var top = 0;
                for (var j = 0; j < table.container.childNodes[i].childNodes.length; j++) {
                    theader.container.childNodes[i].childNodes[j].style.display = "block";
                    theader.container.childNodes[i].childNodes[j].style.top = top + "px";
                    table.container.childNodes[i].childNodes[j].style.display = "block";
                    table.container.childNodes[i].childNodes[j].style.top = top + "px";
                    top = top + rowHeight;
                }
            }
        }
        else {
            theader.container.childNodes[0].deleteCell(num);
            for (var j = 0; j < rows; j++) {
                table.container.childNodes[j].deleteCell(num);
            }
            cols = theader.container.childNodes[0].childNodes.length;
            //var width = 100 / cols;            
        }
        for (var i = 0; i < cols; i++) {
            theader.container.childNodes[0].childNodes[i].attributes[2].value = i;
        }
        resize();
        this.cols = cols;
    }

    this.hideColumn = function (num) {
        theader.container.childNodes[0].childNodes[num].style.display = "none";
        theader.container.childNodes[0].childNodes[num].attributes[3].value = "false"
        for (var j = 0; j < rows; j++) {
            table.container.childNodes[j].childNodes[num].style.display = "none";
            if (vertical) theader.container.childNodes[j].childNodes[num].style.display = "none";
        }
        var shown = 0;
        for (var j = 0; j < cols; j++) {
            if (theader.container.childNodes[0].childNodes[j].style.display != "none") {
                shown = shown + 1;
            }
        }

        if (vertical) {
            for (var i = 0; i < table.container.childNodes.length; i++) {
                theader.container.childNodes[i].style.display = "block";
                theader.container.childNodes[i].style.top = i * rowHeight * shown + "px";
                theader.container.childNodes[i].style.height = rowHeight * shown + "px";
                table.container.childNodes[i].style.display = "block";
                table.container.childNodes[i].style.top = i * rowHeight * shown + "px";
                table.container.childNodes[i].style.height = rowHeight * shown + "px";
                var top = 0;
                for (var j = 0; j < table.container.childNodes[i].childNodes.length; j++) {
                    if (theader.container.childNodes[0].childNodes[j].style.display != "none") {
                        theader.container.childNodes[i].childNodes[j].style.display = "block";
                        theader.container.childNodes[i].childNodes[j].style.top = top + "px";
                        table.container.childNodes[i].childNodes[j].style.display = "block";
                        table.container.childNodes[i].childNodes[j].style.top = top + "px";
                        top = top + rowHeight;
                    }
                    else {
                        theader.container.childNodes[i].childNodes[j].style.display = "none";
                        table.container.childNodes[i].childNodes[j].style.display = "none";
                    }
                }
            }
        }
        resize();
                
    }

    this.displayColumn = function (num) {
        theader.container.childNodes[0].childNodes[num].style.display = "block";
        theader.container.childNodes[0].childNodes[num].attributes[3].value = "true"
        for (var j = 0; j < rows; j++) {
            table.container.childNodes[j].childNodes[num].style.display = "block";
            if (vertical) {
                theader.container.childNodes[j].childNodes[num].style.display = "block";
            }
        }
        var shown = 0;
        for (var j = 0; j < cols; j++) {
            if (theader.container.childNodes[0].childNodes[j].style.display != "none") {
                shown = shown + 1;
            }
        }
        if (vertical) {
            for (var i = 0; i < table.container.childNodes.length; i++) {
                theader.container.childNodes[i].style.display = "block";
                theader.container.childNodes[i].style.top = i * rowHeight * shown + "px";
                theader.container.childNodes[i].style.height = rowHeight * shown + "px";
                table.container.childNodes[i].style.display = "block";
                table.container.childNodes[i].style.top = i * rowHeight * shown + "px";
                table.container.childNodes[i].style.height = rowHeight * shown + "px";
                var top = 0;
                for (var j = 0; j < table.container.childNodes[i].childNodes.length; j++) {
                    if (theader.container.childNodes[0].childNodes[j].style.display != "none") {
                        theader.container.childNodes[i].childNodes[j].style.display = "block";
                        theader.container.childNodes[i].childNodes[j].style.top = top + "px";
                        table.container.childNodes[i].childNodes[j].style.display = "block";
                        table.container.childNodes[i].childNodes[j].style.top = top + "px";
                        top = top + rowHeight;
                    }
                    else {
                        theader.container.childNodes[i].childNodes[j].style.display = "none";
                        table.container.childNodes[i].childNodes[j].style.display = "none";
                    }
                }
            }
        }

        resize();
                
    }

    this.updateRow = function (num, rowData, id) {
        row = table.container.childNodes[num];
        if (id) row.id = id;
        for (var i = 0; i < cols; i++) {
            var rowField = row.childNodes[i];
            if (rowData[i].container) rowField.childNodes[0].innerHTML = rowData[i].container.outerHTML;
            else rowField.childNodes[0].innerHTML = rowData[i];
            rowField.setAttribute("id", rowData[i]);
        }
    }

    function getWidth() {
        var width = [];
        var total = 0;
        for (var i = 0; i < theader.container.childNodes[0].childNodes.length; i++) {
            width[i] = theader.container.childNodes[0].childNodes[i].childNodes[0].clientWidth;
            if (theader.container.childNodes[0].childNodes[i].style.display != "none") {
                for (var j = 0; j < table.container.childNodes.length; j++) {
                    if (table.container.childNodes[j].childNodes[i].childNodes[0].childNodes.length > 0) {
                        var content = table.container.childNodes[j].childNodes[i].childNodes[0].childNodes[0].clientWidth + table.container.childNodes[j].childNodes[i].childNodes[0].childNodes[0].offsetLeft;
                        if (!content > 0) content = table.container.childNodes[j].childNodes[i].childNodes[0].clientWidth + table.container.childNodes[j].childNodes[i].childNodes[0].offsetLeft;
                        if (content > width[i])
                            width[i] = content;
                    }                    
                }
                total = total + width[i];
            }            
        }
        for (var i = 0; i < width.length; i++) width[i] = width[i] * 100 / total;
        return width;
    }

    function resize() {
        if (vertical) {
            var widthTheader = 0;
            var widthTable = 0;
            for (var i = 0; i < theader.container.childNodes[0].childNodes.length; i++) {
                var content = theader.container.childNodes[0].childNodes[i].childNodes[0].childNodes[0].clientWidth + theader.container.childNodes[0].childNodes[i].childNodes[0].childNodes[0].offsetLeft;
                if (!content > 0) content = theader.container.childNodes[0].childNodes[i].childNodes[0].clientWidth + theader.container.childNodes[0].childNodes[i].childNodes[0].offsetLeft;
                if (content > widthTheader) widthTheader = content;
            }
            for (var i = 0; i < table.container.childNodes.length; i++) {
                for (var j = 0; j < table.container.childNodes[i].childNodes.length; j++) {
                    var content = table.container.childNodes[i].childNodes[j].childNodes[0].childNodes[0].clientWidth + table.container.childNodes[i].childNodes[j].childNodes[0].childNodes[0].offsetLeft;
                    if (!content > 0) content =  table.container.childNodes[i].childNodes[j].childNodes[0].clientWidth + table.container.childNodes[i].childNodes[j].childNodes[0].offsetLeft;
                    if (content > widthTable) widthTable = content;
                }                
            }
            /*for (var i = 0; i < theader.container.childNodes.length; i++) {
                for (var j = 0; j < theader.container.childNodes[i].childNodes.length; j++) {
                    theader.container.childNodes[i].childNodes[j].style.width = widthTheader + "%";
                    table.container.childNodes[i].childNodes[j].style.width = widthTable + "%";
                    table.container.childNodes[i].childNodes[j].style.left = widthTheader + "%";
                }
            }*/
            var wh = widthTheader * 100 / (widthTheader + widthTable);
            var wt = widthTable * 100 / (widthTheader + widthTable);
            theader.container.style.width = wh + "%";
            table.container.style.width = wt + "%";
            table.container.style.left = wh + "%";
        }
        else {
            var width = getWidth();
            var left = 0;
            for (var i = 0; i < theader.container.childNodes[0].childNodes.length; i++) {
                if (theader.container.childNodes[0].childNodes[i].style.display != "none") {
                    theader.container.childNodes[0].childNodes[i].style.display = "block";
                    theader.container.childNodes[0].childNodes[i].style.width = width[i] + "%";
                    theader.container.childNodes[0].childNodes[i].style.left = left + "%";
                    for (var j = 0; j < table.container.childNodes.length; j++) {
                        table.container.childNodes[j].childNodes[i].style.display = "block";
                        table.container.childNodes[j].childNodes[i].style.width = width[i] + "%";
                        table.container.childNodes[j].childNodes[i].style.left = left + "%";
                    }
                    left = left + width[i];
                }
            }
        }        
    }

    this.resizeTable = function () {
        resize();
    }

    this.search = function (text) {
        var top = 0;
        var filter = text.toUpperCase();
        filter = filter.normalize('NFD').replace(/[\u0300-\u036f]/g, "");
        filteredRows = 0;
        if (vertical) {
            for (var i = 0; i < rows; i++) {
                var hV = 0;
                for (var j = 0; j < cols; j++) {
                    if (theader.container.childNodes[0].childNodes[j].attributes[3].value == "true") {
                        theader.container.childNodes[i].childNodes[j].style.display = "block";
                        table.container.childNodes[i].childNodes[j].style.display = "block";
                        theader.container.childNodes[i].childNodes[j].style.top = hV + "px";
                        table.container.childNodes[i].childNodes[j].style.top = hV + "px";
                        hV = hV + rowHeight;
                    } else {
                        theader.container.childNodes[i].childNodes[j].style.display = "none";
                        table.container.childNodes[i].childNodes[j].style.display = "none";
                    }
                }
                theader.container.childNodes[i].style.height = hV + "px";
                table.container.childNodes[i].style.height = hV + "px";
                for (var j = 0; j < cols; j++) {
                    if (table.container.childNodes[i].childNodes[j].id.toUpperCase().normalize('NFD').replace(/[\u0300-\u036f]/g, "").indexOf(filter) > -1) {
                        theader.container.childNodes[i].style.display = "block";
                        theader.container.childNodes[i].style.top = top + "px";
                        table.container.childNodes[i].style.display = "block";
                        table.container.childNodes[i].style.top = top + "px";
                        j = cols + 1;
                        top = top + hV;
                        filteredRows = filteredRows + 1;
                    } else if (j == cols - 1) {
                        table.container.childNodes[i].style.display = "none";
                        theader.container.childNodes[i].style.display = "none";
                    }
                }
            }
        }
        else {
            for (var i = 0; i < rows; i++) {
                for (var j = 0; j < cols; j++) {
                    if (table.container.childNodes[i].childNodes[j].id.toUpperCase().normalize('NFD').replace(/[\u0300-\u036f]/g, "").indexOf(filter) > -1) {
                        table.container.childNodes[i].style.display = "block";
                        table.container.childNodes[i].style.top = top + "px";
                        j = cols + 1;
                        top = top + rowHeight;
                        filteredRows = filteredRows + 1;
                    } else if (j == cols - 1) {
                        table.container.childNodes[i].style.display = "none";
                    }
                }
            }
        }
        table.container.style.height = top + "px";
    }

    function sortTable(event, headerS, id) {
        if (!id >= 0) id = headerS.container.attributes[4].value;
        if (document.body.style.cursor != "col-resize" && dragging == null) {
            var col = headerS.container.attributes[2].value;
            var asc = headerS.container.attributes[1].value;
            var int = headerS.container.attributes[5].value;
            if (sortArrow != null) {
                if (sortArrow.parentElement != null) sortArrow.parentElement.rem(sortArrow);
            }
            if (asc == "true") {
                headerS.container.attributes[1].value = "false";
                headerS.add(sortArrow);
                sortArrow.container.style.transform = "rotate(90deg)";
                sortArrow.container.style.webkitTransform = "rotate(90deg)";
            }
            else {
                headerS.container.attributes[1].value = "true";
                headerS.add(sortArrow);
                sortArrow.container.style.transform = "rotate(270deg)";
                sortArrow.container.style.webkitTransform = "rotate(270deg)";
            }
            sortArrow.container.style.display = "block";

            var rows, switching, i, x, y;
            switching = true;
            while (switching) {
                switching = false;
                rows = table.container.rows;
                for (i = 0; i < (rows.length - 1) ; i++) {
                    shouldSwitch = false;
                    x = rows[i].childNodes[col].id;
                    y = rows[i + 1].childNodes[col].id;
                    if (asc == "true") {
                        if (int=="true") {
                            if (parseInt(x) > parseInt(y)) {
                                switching = true;
                                var top1 = rows[i].style.top;
                                var top2 = rows[i + 1].style.top;
                                rows[i].style.top = top2;
                                rows[i + 1].style.top = top1;
                                table.container.insertBefore(table.container.rows[i + 1], table.container.rows[i]);
                            }
                        }
                        else if (x.localeCompare(y) > 0) {
                            switching = true;
                            var top1 = rows[i].style.top;
                            var top2 = rows[i + 1].style.top;
                            rows[i].style.top = top2;
                            rows[i + 1].style.top = top1;
                            table.container.insertBefore(table.container.rows[i + 1], table.container.rows[i]);
                        }
                    }
                    else {
                        if (int == "true") {
                            if (parseInt(x) < parseInt(y)) {
                                switching = true;
                                var top1 = rows[i].style.top;
                                var top2 = rows[i + 1].style.top;
                                rows[i].style.top = top2;
                                rows[i + 1].style.top = top1;
                                table.container.insertBefore(table.container.rows[i + 1], table.container.rows[i]);
                            }
                        }
                        else if (x.localeCompare(y) < 0) {
                            switching = true;
                            var top1 = rows[i].style.top;
                            var top2 = rows[i + 1].style.top;
                            rows[i].style.top = top2;
                            rows[i + 1].style.top = top1;
                            table.container.insertBefore(table.container.rows[i + 1], table.container.rows[i]);
                        }
                    }
                }
            }
            var top = 0;
            for (var i = 0; i < table.container.childNodes.length; i++) {
                var inc = 0;
                if (table.container.childNodes[i].style.display != "none") {
                    table.container.childNodes[i].style.top = top + "px";
                    top = top + rowHeight;
                }
            }
        }
    }

    function sortTableVertical(event, headerS, id) {
        if (!id >= 0) id = headerS.container.attributes[4].value;
        var col = headerS.container.attributes[2].value;
        var asc = headerS.container.attributes[1].value;
        var int = headerS.container.attributes[5].value;
        if (sortArrow != null) {
            if (sortArrow.parentElement != null) sortArrow.parentElement.rem(sortArrow);
        }
        if (asc == "true") {
            headerS.container.attributes[1].value = "false";
            headerS.add(sortArrow);
            sortArrow.container.style.transform = "rotate(90deg)";
            sortArrow.container.style.webkitTransform = "rotate(90deg)";
        }
        else {
            headerS.container.attributes[1].value = "true";
            headerS.add(sortArrow);
            sortArrow.container.style.transform = "rotate(270deg)";
            sortArrow.container.style.webkitTransform = "rotate(270deg)";
        }
        sortArrow.container.style.display = "block";

        var rows, switching, i, x, y;
        switching = true;
        while (switching) {
            switching = false;
            rows = table.container.rows;
            for (i = 0; i < (rows.length - 1) ; i++) {
                shouldSwitch = false;
                x = rows[i].childNodes[col].id;
                y = rows[i + 1].childNodes[col].id;
                if (asc == "true") {
                    if (int == "true") {
                        if (parseInt(x) > parseInt(y)) {
                            switching = true;
                            var top1 = rows[i].style.top;
                            var top2 = rows[i + 1].style.top;
                            rows[i].style.top = top2;
                            rows[i + 1].style.top = top1;
                            table.container.insertBefore(table.container.rows[i + 1], table.container.rows[i]);
                        }
                    }
                    else if (x.localeCompare(y) > 0) {
                        switching = true;
                        var top1 = rows[i].style.top;
                        var top2 = rows[i + 1].style.top;
                        rows[i].style.top = top2;
                        rows[i + 1].style.top = top1;
                        table.container.insertBefore(table.container.rows[i + 1], table.container.rows[i]);
                    }
                }
                else {
                    if (int == "true") {
                        if (parseInt(x) < parseInt(y)) {
                            switching = true;
                            var top1 = rows[i].style.top;
                            var top2 = rows[i + 1].style.top;
                            rows[i].style.top = top2;
                            rows[i + 1].style.top = top1;
                            table.container.insertBefore(table.container.rows[i + 1], table.container.rows[i]);
                        }
                    }
                    else if (x.localeCompare(y) < 0) {
                        switching = true;
                        var top1 = rows[i].style.top;
                        var top2 = rows[i + 1].style.top;
                        rows[i].style.top = top2;
                        rows[i + 1].style.top = top1;
                        table.container.insertBefore(table.container.rows[i + 1], table.container.rows[i]);
                    }
                }
            }
        }
        var top = 0;
        for (var i = 0; i < table.container.childNodes.length; i++) {
            if (table.container.childNodes[i].style.display != "none") {
                table.container.childNodes[i].style.top = top + "px";
                top = top + rowHeight * cols;
            }
        }
    }

}

innovaphone.ui1.ListView.prototype = innovaphone.ui1.nodePrototype;