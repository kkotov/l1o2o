require(rCharts)

shinyUI(navbarPage("EMTF Link Alignment",

  tabPanel("ME1a",
    sidebarLayout(
      sidebarPanel(
        uiOutput("me1a_links"),
        uiOutput("me1a_run_length")
      ),
      mainPanel(
        tabsetPanel(
          tabPanel("EMTF-1", showOutput("emtf_me1a_n1", "dimple"), value=4),
          tabPanel("EMTF-2", showOutput("emtf_me1a_n2", "dimple"), value=4),
          tabPanel("EMTF-3", showOutput("emtf_me1a_n3", "dimple"), value=4),
          tabPanel("EMTF-4", showOutput("emtf_me1a_n4", "dimple"), value=4),
          tabPanel("EMTF-5", showOutput("emtf_me1a_n5", "dimple"), value=4),
          tabPanel("EMTF-6", showOutput("emtf_me1a_n6", "dimple"), value=4),
          tabPanel("EMTF+1", showOutput("emtf_me1a_p1", "dimple"), value=4),
          tabPanel("EMTF+2", showOutput("emtf_me1a_p2", "dimple"), value=4),
          tabPanel("EMTF+3", showOutput("emtf_me1a_p3", "dimple"), value=4),
          tabPanel("EMTF+4", showOutput("emtf_me1a_p4", "dimple"), value=4),
          tabPanel("EMTF+5", showOutput("emtf_me1a_p5", "dimple"), value=4),
          tabPanel("EMTF+6", showOutput("emtf_me1a_p6", "dimple"), value=4),
          id="conditionedPanels"
        )
      )
    )
  ),

  tabPanel("ME1b",
    sidebarLayout(
      sidebarPanel(
        uiOutput("me1b_links"),
        uiOutput("me1b_run_length")
      ),
      mainPanel(
        tabsetPanel(
          tabPanel("EMTF-1", showOutput("emtf_me1b_n1", "dimple"), value=4),
          tabPanel("EMTF-2", showOutput("emtf_me1b_n2", "dimple"), value=4),
          tabPanel("EMTF-3", showOutput("emtf_me1b_n3", "dimple"), value=4),
          tabPanel("EMTF-4", showOutput("emtf_me1b_n4", "dimple"), value=4),
          tabPanel("EMTF-5", showOutput("emtf_me1b_n5", "dimple"), value=4),
          tabPanel("EMTF-6", showOutput("emtf_me1b_n6", "dimple"), value=4),
          tabPanel("EMTF+1", showOutput("emtf_me1b_p1", "dimple"), value=4),
          tabPanel("EMTF+2", showOutput("emtf_me1b_p2", "dimple"), value=4),
          tabPanel("EMTF+3", showOutput("emtf_me1b_p3", "dimple"), value=4),
          tabPanel("EMTF+4", showOutput("emtf_me1b_p4", "dimple"), value=4),
          tabPanel("EMTF+5", showOutput("emtf_me1b_p5", "dimple"), value=4),
          tabPanel("EMTF+6", showOutput("emtf_me1b_p6", "dimple"), value=4),
          id="conditionedPanels"
        )
      )
    )
  ),

  tabPanel("ME2",
    sidebarLayout(
      sidebarPanel(
        uiOutput("me2_links"),
        uiOutput("me2_run_length")
      ),
      mainPanel(
        tabsetPanel(
          tabPanel("EMTF-1", showOutput("emtf_me2_n1", "dimple"), value=4),
          tabPanel("EMTF-2", showOutput("emtf_me2_n2", "dimple"), value=4),
          tabPanel("EMTF-3", showOutput("emtf_me2_n3", "dimple"), value=4),
          tabPanel("EMTF-4", showOutput("emtf_me2_n4", "dimple"), value=4),
          tabPanel("EMTF-5", showOutput("emtf_me2_n5", "dimple"), value=4),
          tabPanel("EMTF-6", showOutput("emtf_me2_n6", "dimple"), value=4),
          tabPanel("EMTF+1", showOutput("emtf_me2_p1", "dimple"), value=4),
          tabPanel("EMTF+2", showOutput("emtf_me2_p2", "dimple"), value=4),
          tabPanel("EMTF+3", showOutput("emtf_me2_p3", "dimple"), value=4),
          tabPanel("EMTF+4", showOutput("emtf_me2_p4", "dimple"), value=4),
          tabPanel("EMTF+5", showOutput("emtf_me2_p5", "dimple"), value=4),
          tabPanel("EMTF+6", showOutput("emtf_me2_p6", "dimple"), value=4),
          id="conditionedPanels"
        )
      )
    )
  ),

  tabPanel("ME3",
    sidebarLayout(
      sidebarPanel(
        uiOutput("me3_links"),
        uiOutput("me3_run_length")
      ),
      mainPanel(
        tabsetPanel(
          tabPanel("EMTF-1", showOutput("emtf_me3_n1", "dimple"), value=4),
          tabPanel("EMTF-2", showOutput("emtf_me3_n2", "dimple"), value=4),
          tabPanel("EMTF-3", showOutput("emtf_me3_n3", "dimple"), value=4),
          tabPanel("EMTF-4", showOutput("emtf_me3_n4", "dimple"), value=4),
          tabPanel("EMTF-5", showOutput("emtf_me3_n5", "dimple"), value=4),
          tabPanel("EMTF-6", showOutput("emtf_me3_n6", "dimple"), value=4),
          tabPanel("EMTF+1", showOutput("emtf_me3_p1", "dimple"), value=4),
          tabPanel("EMTF+2", showOutput("emtf_me3_p2", "dimple"), value=4),
          tabPanel("EMTF+3", showOutput("emtf_me3_p3", "dimple"), value=4),
          tabPanel("EMTF+4", showOutput("emtf_me3_p4", "dimple"), value=4),
          tabPanel("EMTF+5", showOutput("emtf_me3_p5", "dimple"), value=4),
          tabPanel("EMTF+6", showOutput("emtf_me3_p6", "dimple"), value=4),
          id="conditionedPanels"
        )
      )
    )
  ),

  tabPanel("ME4",
    sidebarLayout(
      sidebarPanel(
        uiOutput("me4_links"),
        uiOutput("me4_run_length")
      ),
      mainPanel(
        tabsetPanel(
          tabPanel("EMTF-1", showOutput("emtf_me4_n1", "dimple"), value=4),
          tabPanel("EMTF-2", showOutput("emtf_me4_n2", "dimple"), value=4),
          tabPanel("EMTF-3", showOutput("emtf_me4_n3", "dimple"), value=4),
          tabPanel("EMTF-4", showOutput("emtf_me4_n4", "dimple"), value=4),
          tabPanel("EMTF-5", showOutput("emtf_me4_n5", "dimple"), value=4),
          tabPanel("EMTF-6", showOutput("emtf_me4_n6", "dimple"), value=4),
          tabPanel("EMTF+1", showOutput("emtf_me4_p1", "dimple"), value=4),
          tabPanel("EMTF+2", showOutput("emtf_me4_p2", "dimple"), value=4),
          tabPanel("EMTF+3", showOutput("emtf_me4_p3", "dimple"), value=4),
          tabPanel("EMTF+4", showOutput("emtf_me4_p4", "dimple"), value=4),
          tabPanel("EMTF+5", showOutput("emtf_me4_p5", "dimple"), value=4),
          tabPanel("EMTF+6", showOutput("emtf_me4_p6", "dimple"), value=4),
          id="conditionedPanels"
        )
      )
    )
  ),

  tabPanel("MEn",
    sidebarLayout(
      sidebarPanel(
        uiOutput("men_links"),
        uiOutput("men_run_length")
      ),
      mainPanel(
        tabsetPanel(
          tabPanel("EMTF-1", showOutput("emtf_men_n1", "dimple"), value=4),
          tabPanel("EMTF-2", showOutput("emtf_men_n2", "dimple"), value=4),
          tabPanel("EMTF-3", showOutput("emtf_men_n3", "dimple"), value=4),
          tabPanel("EMTF-4", showOutput("emtf_men_n4", "dimple"), value=4),
          tabPanel("EMTF-5", showOutput("emtf_men_n5", "dimple"), value=4),
          tabPanel("EMTF-6", showOutput("emtf_men_n6", "dimple"), value=4),
          tabPanel("EMTF+1", showOutput("emtf_men_p1", "dimple"), value=4),
          tabPanel("EMTF+2", showOutput("emtf_men_p2", "dimple"), value=4),
          tabPanel("EMTF+3", showOutput("emtf_men_p3", "dimple"), value=4),
          tabPanel("EMTF+4", showOutput("emtf_men_p4", "dimple"), value=4),
          tabPanel("EMTF+5", showOutput("emtf_men_p5", "dimple"), value=4),
          tabPanel("EMTF+6", showOutput("emtf_men_p6", "dimple"), value=4),
          id="conditionedPanels"
        )
      )
    )
  ),

  tabPanel("All",
    sidebarLayout(
      sidebarPanel(
        uiOutput("all_links"),
        uiOutput("all_run_length")
      ),
      mainPanel(
        tabsetPanel(
          tabPanel("EMTF-1", showOutput("emtf_all_n1", "dimple"), value=4),
          tabPanel("EMTF-2", showOutput("emtf_all_n2", "dimple"), value=4),
          tabPanel("EMTF-3", showOutput("emtf_all_n3", "dimple"), value=4),
          tabPanel("EMTF-4", showOutput("emtf_all_n4", "dimple"), value=4),
          tabPanel("EMTF-5", showOutput("emtf_all_n5", "dimple"), value=4),
          tabPanel("EMTF-6", showOutput("emtf_all_n6", "dimple"), value=4),
          tabPanel("EMTF+1", showOutput("emtf_all_p1", "dimple"), value=4),
          tabPanel("EMTF+2", showOutput("emtf_all_p2", "dimple"), value=4),
          tabPanel("EMTF+3", showOutput("emtf_all_p3", "dimple"), value=4),
          tabPanel("EMTF+4", showOutput("emtf_all_p4", "dimple"), value=4),
          tabPanel("EMTF+5", showOutput("emtf_all_p5", "dimple"), value=4),
          tabPanel("EMTF+6", showOutput("emtf_all_p6", "dimple"), value=4),
          id="conditionedPanels"
        )
      )
    )
  )

))
