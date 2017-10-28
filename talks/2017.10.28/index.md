---
title       : "Link Alignments"
subtitle    : 
author      : Khristian Kotov
job         : 
framework   : io2012        # {io2012, html5slides, shower, dzslides, ...}
highlighter : highlight.js  # {highlight.js, prettify, highlight}
hitheme     : tomorrow      # 
github:
  user: kkotov 
  repo: talks
url:
  lib:    ../../../../monohiggs/plots/libraries
  assets: ../../../../monohiggs/plots/assets
widgets     : [mathjax]     # {mathjax, quiz, bootstrap}
ext_widgets : {rCharts: [libraries/nvd3, libraries/polycharts]}
mode        : selfcontained # {standalone, draft}
knit        : slidify::knit2slides

--- .class #id

## EMTF-1 / ME1a

<div align="center">

<div id = 'chart46b32017b15f' class = 'rChart polycharts'></div>
<script type='text/javascript'>
    var chartParams = {
 "dom": "chart46b32017b15f",
"width":    850,
"height":    350,
"layers": [
 {
 "x": "width",
"y": "found",
"data": {
 "width": [      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13,     14,     15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     29,     30,     31,     32 ],
"found": [      2,      4,      6,      8,     10,     12,  13.99,  15.89,  17.36,  18.24,  18.71,  18.97,  19.13,  19.25,  19.36,  19.46,  19.55,  19.63,  19.72,  19.79,  19.87,  19.94,  20.01,  20.07,  20.14,   20.2,  20.26,  20.32,  20.38,  20.43,  20.48,   20.5 ] 
},
"facet": null,
"type": "point" 
} 
],
"facet": [],
"guides": {
 "x": {
 "min":    0.5,
"max":   32.5,
"numticks": 32,
"title": "pattern length (symbols)" 
},
"y": {
 "min":      0,
"max":     22 
} 
},
"coord": [],
"title": "log2(# of unique patterns)",
"id": "chart46b32017b15f" 
}
    _.each(chartParams.layers, function(el){
        el.data = polyjs.data(el.data)
    })
    var graph_chart46b32017b15f = polyjs.chart(chartParams);
</script>
</div>
