library(dygraphs)
library(timeSeries)
library(rCharts)

links1a = c("me1a_02", "me1a_03", "me1a_04", "me1a_05", "me1a_06", "me1a_07", "me1a_08", "me1a_09")
links1b = c("me1b_02", "me1b_03", "me1b_04", "me1b_05", "me1b_06", "me1b_07", "me1b_08", "me1b_09")
links2  = c("me2_02",  "me2_03",  "me2_04",  "me2_05",  "me2_06",  "me2_07",  "me2_08",  "me2_09")
links3  = c("me3_02",  "me3_03",  "me3_04",  "me3_05",  "me3_06",  "me3_07",  "me3_08",  "me3_09")
links4  = c("me4_02",  "me4_03",  "me4_04",  "me4_05",  "me4_06",  "me4_07",  "me4_08",  "me4_09")
linksn  = c("me1n_03", "me1n_06", "me1n_09", "me2n_03", "me2n_09", "me3n_03", "me3n_09", "me4n_03", "me4n_09")
procs   = c("EMTF-1",  "EMTF-2",  "EMTF-3",  "EMTF-4",  "EMTF-5",  "EMTF-6",
            "EMTF+1",  "EMTF+2",  "EMTF+3",  "EMTF+4",  "EMTF+5",  "EMTF+6")

flatten <- function(fileName) {
    dr <- read.csv(file=fileName,header=T,sep=',')
    df <- data.frame(time = character(), delay = numeric(), link = factor(), board = factor())
    for(link in c(links1a, links1b, links2, links3, links4, linksn) ){
        df <- rbind(df, data.frame(time = dr$DateTime, delay = dr[,link], link = rep(link,nrow(dr)), board = procs[1]) )
    }
    return(df)
}

df <- flatten("drifts.csv")

checkLinks <- function(links,selected=T){
}

makeChart <- function(name,links,brd){
    d1 <- dPlot(x="time", y="delay", groups = c("link"), data = subset(df,(link %in% links) & board==brd), type = "bubble")
    d1$xAxis(type = "addTimeAxis", inputFormat = "%Y.%m.%d %H:%M:%S", outputFormat = "%Y-%m-%d %H:%M") 
    d1$legend(x = 60, y = 10, width = 700, height = 20, horizontalAlign = "right")
    d1$addParams(dom = name)
    return(d1)
}

shinyServer(
  function(input, output) {

    output$me1a_links <- renderUI({ checkboxGroupInput('show_me1a_links', 'Links to show:', links1a, selected = links1a) })
    output$me1b_links <- renderUI({ checkboxGroupInput('show_me1b_links', 'Links to show:', links1b, selected = links1b) })
    output$me2_links  <- renderUI({ checkboxGroupInput('show_me2_links',  'Links to show:', links2,  selected = links2) })
    output$me3_links  <- renderUI({ checkboxGroupInput('show_me3_links',  'Links to show:', links3,  selected = links3) })
    output$me4_links  <- renderUI({ checkboxGroupInput('show_me4_links',  'Links to show:', links4,  selected = links4) })
    output$men_links  <- renderUI({ checkboxGroupInput('show_men_links',  'Links to show:', linksn,  selected = linksn) })
    output$all_links  <- renderUI({ checkboxGroupInput('show_all_links',  'Links to show:', c(links1a,links1b,links2,links3,links4,linksn), selected = c()) })

    output$me1a_run_length <- renderUI({ sliderInput('me1a_rl', 'Run Length', value = 0, min = 0, max = 100, step = 1) })
    output$me1b_run_length <- renderUI({ sliderInput('me1b_rl', 'Run Length', value = 0, min = 0, max = 100, step = 1) })
    output$me2_run_length  <- renderUI({ sliderInput('me2_rl',  'Run Length', value = 0, min = 0, max = 100, step = 1) })
    output$me3_run_length  <- renderUI({ sliderInput('me3_rl',  'Run Length', value = 0, min = 0, max = 100, step = 1) })
    output$me4_run_length  <- renderUI({ sliderInput('me4_rl',  'Run Length', value = 0, min = 0, max = 100, step = 1) })
    output$men_run_length  <- renderUI({ sliderInput('men_rl',  'Run Length', value = 0, min = 0, max = 100, step = 1) })
    output$all_run_length  <- renderUI({ sliderInput('all_rl',  'Run Length', value = 0, min = 0, max = 100, step = 1) })

    output$emtf_me1a_n1 <- renderChart({ makeChart("emtf_me1a_n1", input$show_me1a_links, "EMTF-1") })
    output$emtf_me1b_n1 <- renderChart({ makeChart("emtf_me1b_n1", input$show_me1b_links, "EMTF-1") })
    output$emtf_me2_n1 <- renderChart({ makeChart("emtf_me2_n1", input$show_me2_links, "EMTF-1") })
    output$emtf_me3_n1 <- renderChart({ makeChart("emtf_me3_n1", input$show_me3_links, "EMTF-1") })
    output$emtf_me4_n1 <- renderChart({ makeChart("emtf_me4_n1", input$show_me4_links, "EMTF-1") })
    output$emtf_men_n1 <- renderChart({ makeChart("emtf_men_n1", input$show_me4_links, "EMTF-1") })
    output$emtf_all_n1 <- renderChart({ makeChart("emtf_all_n1", input$show_all_links, "EMTF-1") })

  }
)
