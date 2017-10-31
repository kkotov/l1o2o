sink('analysis-output.txt')

for(sector in seq(1,6)){
for(endcap in c(1,2)){
side = ifelse(endcap==1, "+", "-")
name = paste0("EMTF",side,sector,"_2017.10.30_19:52:31")
system(paste0("cat ",name," | sed -e 's|  |,|g' -e 's|,$||g' > tmp.csv"))
df <- read.csv(file="tmp.csv", header=F, sep=',')
links <- c("me1a_02","me1a_03", "me1a_04", "me1a_05", "me1a_06", "me1a_07", "me1a_08", "me1a_09", "me1b_02", "me1b_03", "me1b_04", "me1b_05", "me1b_06", "me1b_07", "me1b_08", "me1b_09", "me2_02", "me2_03", "me2_04", "me2_05", "me2_06", "me2_07", "me2_08", "me2_09", "me3_02", "me3_03", "me3_04", "me3_05", "me3_06", "me3_07", "me3_08", "me3_09", "me4_02", "me4_03", "me4_04", "me4_05", "me4_06", "me4_07", "me4_08", "me4_09", "me1n_03", "me1n_06", "me1n_09", "me2n_03", "me2n_09", "me3n_03", "me3n_09", "me4n_03", "me4n_09")
colnames(df) <- links
d <- sapply( links, function(x){ mean( df[abs(df[,x] - mean(df[,x])) < 20, x] ) } )
sapply(names(d), function(x){ cat(paste0("{\"",endcap,"_",sector,"_",x,"\",",round(d[x]),"},")) })
cat("\n")
}
}

sink()
