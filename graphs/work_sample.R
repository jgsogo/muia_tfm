# Work over results

library(data.table)
require(ggplot2)
library(reshape)
source("summarySE.R")


parse_sample <- function(file) {
    data <- data.frame(read.csv(file=file, header=TRUE, sep="\t"))
}

plot_synset_tol <- function(data, title, img_name) {
    # Credit: http://www.cookbook-r.com/Graphs/Plotting_means_and_error_bars_(ggplot2)/   
    d_sub <- subset(data, relation.tolerance==0)
    d_sub <- d_sub[, c("translator", "synset.tolerance", "similarity.value")]
    colnames(d_sub) <- c("Traductor", "tol", "sim")
    d_sub$Traductor <- factor(d_sub$Traductor, levels=c("google", "yandex"), labels=c("Google", "Yandex"))
    
    tgc <- summarySE(d_sub, measurevar="sim", groupvars=c("Traductor", "tol"))

    # Standard error of the mean
    pd <- position_dodge(0.01) # move them .05 to the left and right
    g <- ggplot(tgc, aes(x=tol, y=sim, colour=Traductor)) + 
         geom_errorbar(aes(ymin=sim-se, ymax=sim+se), width=.1, position=pd) +
         geom_line() +
         geom_point() +
#          ylim(0.0, 1.0) +
         ylab("Similaridad") + xlab("Tolerancia entre conceptos\nTolerancia entre relaciones = 0.0") +
         labs(title=title)
    
    ggsave(paste(img_name, "synset_tol.png", sep="-"), g)
    g
}

plot_relation_tol <- function(data, title, img_name) {
    # Credit: http://www.cookbook-r.com/Graphs/Plotting_means_and_error_bars_(ggplot2)/   
    d_sub <- subset(data, synset.tolerance==0)
    d_sub <- d_sub[, c("translator", "relation.tolerance", "similarity.value")]
    colnames(d_sub) <- c("Traductor", "tol", "sim")
    d_sub$Traductor <- factor(d_sub$Traductor, levels=c("google", "yandex"), labels=c("Google", "Yandex"))
    
    tgc <- summarySE(d_sub, measurevar="sim", groupvars=c("Traductor", "tol"))
    
    # Standard error of the mean
    pd <- position_dodge(0.01) # move them .05 to the left and right
    g <- ggplot(tgc, aes(x=tol, y=sim, colour=Traductor)) + 
        geom_errorbar(aes(ymin=sim-se, ymax=sim+se), width=.1, position=pd) +
        geom_line() +
        geom_point() +
#         ylim(0.0, 1.0) +
        ylab("Similaridad") + xlab("Tolerancia entre relaciones\nTolerancia entre conceptos = 0.0") +
        labs(title=title)
    
    ggsave(paste(img_name, "relation_tol.png", sep="-"), g)
    g
}


work_sample <- function(file, title) {
    data <- parse_sample(file)
    img_name = substr(file, 0, which(strsplit(file, '')[[1]]=='-')-1)
    plot_synset_tol(data, title, img_name)    
    plot_relation_tol(data, title, img_name)

}

