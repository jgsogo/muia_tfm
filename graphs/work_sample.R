# Work over results

library(data.table)
require(ggplot2)
library(reshape)
source("summarySE.R")


parse_sample <- function(file) {
    data <- data.frame(read.csv(file=file, header=TRUE, sep="\t"))
}

plot_synset_tol <- function(data, title, save_path) {
    # Credit: http://www.cookbook-r.com/Graphs/Plotting_means_and_error_bars_(ggplot2)/   
    tol_rel_values = unique(data[, c("relation.tolerance")])
    for (tol_rel in tol_rel_values) {
      d_sub <- subset(data, relation.tolerance==tol_rel)
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
           ylab("Similaridad") + xlab(paste("Tolerancia entre conceptos\nTolerancia entre relaciones = ", tol_rel, sep="")) +
           labs(title=title)
      
      filename = paste("synset_tol", "relation_tol", tol_rel, sep="-")
      filename = paste(filename, "png", sep=".")
      filepath = file.path(save_path, filename)
      print(filepath)
      g
      ggsave(filepath, g)
    }
}

plot_relation_tol <- function(data, title, save_path) {
    # Credit: http://www.cookbook-r.com/Graphs/Plotting_means_and_error_bars_(ggplot2)/   
    tol_syn_values = unique(data[, c("synset.tolerance")])
    for (tol_syn in tol_syn_values) {
      d_sub <- subset(data, synset.tolerance==tol_syn)
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
          ylab("Similaridad") + xlab(paste("Tolerancia entre relaciones\nTolerancia entre conceptos = ", tol_syn, sep="")) +
          labs(title=title)
      
      filename = paste("relation_tol", "synset_tol", tol_syn, sep="-")
      filename = paste(filename, "png", sep=".")
      filepath = file.path(save_path, filename)
      print(filepath)
      g
      ggsave(filepath, g)
    }
}


work_sample <- function(file, title) {
    data <- parse_sample(file)

    filepath = dirname(file)
    img_name = basename(file)
    img_name = substr(img_name, 0, which(strsplit(img_name, '')[[1]]=='.')-1)
    save_path = file.path(filepath, paste(img_name, "brief", sep="-"))
    
    dir.create(save_path, showWarnings = FALSE)
    
    plot_synset_tol(data, title, save_path)    
    plot_relation_tol(data, title, save_path)

}
