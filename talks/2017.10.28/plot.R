library(rCharts)
dr <- read.csv(file="drifts.csv",header=T,sep=',')
td <- as.double(as.POSIXct(as.character(dr$DateTime),format="%Y.%m.%d %H:%M:%S", tz = "GMT"))

df <-           data.frame(td = td, align = dr$me1a_02, link = rep("me1a_02",length(td)))
df <- rbind(df, data.frame(td = td, align = dr$me1a_03, link = rep("me1a_03",length(td))) )
df <- rbind(df, data.frame(td = td, align = dr$me1a_04, link = rep("me1a_04",length(td))) )
df <- rbind(df, data.frame(td = td, align = dr$me1a_05, link = rep("me1a_05",length(td))) )
df <- rbind(df, data.frame(td = td, align = dr$me1a_06, link = rep("me1a_06",length(td))) )
df <- rbind(df, data.frame(td = td, align = dr$me1a_07, link = rep("me1a_07",length(td))) )
df <- rbind(df, data.frame(td = td, align = dr$me1a_08, link = rep("me1a_08",length(td))) )
df <- rbind(df, data.frame(td = td, align = dr$me1a_09, link = rep("me1a_09",length(td))) )

r1 <- Rickshaw$new()
r1$layer(align ~ td, data = df[,c("td","align","link")], groups = "link", type = "scatterplot")
r1$set(slider = TRUE)
r1

#$print("chart3")

