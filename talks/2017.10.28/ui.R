library(rCharts)

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
          id="conditionedPanels"
        )
      )
    )
  )

))
