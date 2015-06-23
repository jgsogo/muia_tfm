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
      ggsave(filepath, g, width=7, height=4)
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
      ggsave(filepath, g, width=7, height=4)
    }
}

plot_distances_synset <- function(data, title, save_path, tol_relation = 0.0) {
    distance_measures <- unique(data[, c("distance.meassure")])
    translators <- unique(data[, c("translator")])
    data <- subset(data, relation.tolerance==tol_relation)
    data <- data[, c("translator", "distance.meassure", "synset.tolerance", "similarity.value")]
    
    colnames(data) <- c("Traductor", "Medida", "tol", "sim")
    
    # Google
    google_data <- subset(data, Traductor=="google")
    google_data <- google_data[, c("Medida", "tol", "sim")]
    
    g <- ggplot(google_data, aes(x=tol, y=sim, colour=Medida)) + 
        geom_line() +
        geom_point() +
        ylab("Similaridad") + xlab(paste("Tolerancia entre conceptos\nTolerancia entre relaciones = ", tol_relation, sep="")) +
        labs(title=title)
    
    # Yandex
    yandex_data <- subset(data, Traductor=="yandex")
    yandex_data <- yandex_data[, c("Medida", "tol", "sim")]
    
    y <- ggplot(yandex_data, aes(x=tol, y=sim, colour=Medida)) + 
        geom_line() +
        geom_point() +
        ylab("Similaridad") + xlab(paste("Tolerancia entre conceptos\nTolerancia entre relaciones = ", tol_relation, sep="")) +
        labs(title=title)
    
    # Save to files
    file_google = paste("measures-google-synset", "png", sep=".")
    filepath = file.path(save_path, file_google)
    ggsave(filepath, g, width=7, height=4)    
    
    file_yandex = paste("measures-yandex-synset", "png", sep=".")
    filepath = file.path(save_path, file_yandex)
    ggsave(filepath, y, width=7, height=4)    
}


plot_distances_relation <- function(data, title, save_path, tol_synset = 0.0) {
    distance_measures <- unique(data[, c("distance.meassure")])
    translators <- unique(data[, c("translator")])
    data <- subset(data, synset.tolerance==tol_synset)
    data <- data[, c("translator", "distance.meassure", "relation.tolerance", "similarity.value")]
    
    colnames(data) <- c("Traductor", "Medida", "tol", "sim")
    
    # Google
    google_data <- subset(data, Traductor=="google")
    google_data <- google_data[, c("Medida", "tol", "sim")]
    
    g <- ggplot(google_data, aes(x=tol, y=sim, colour=Medida)) + 
        geom_line() +
        geom_point() +
        ylab("Similaridad") + xlab(paste("Tolerancia entre relaciones\nTolerancia entre conceptos = ", tol_synset, sep="")) +
        labs(title=title)
    
    # Yandex
    yandex_data <- subset(data, Traductor=="yandex")
    yandex_data <- yandex_data[, c("Medida", "tol", "sim")]
    
    y <- ggplot(yandex_data, aes(x=tol, y=sim, colour=Medida)) + 
        geom_line() +
        geom_point() +
        ylab("Similaridad") + xlab(paste("Tolerancia entre relaciones\nTolerancia entre conceptos = ", tol_synset, sep="")) +
        labs(title=title)
    
    # Save to files
    file_google = paste("measures-google-relation", "png", sep=".")
    filepath = file.path(save_path, file_google)
    ggsave(filepath, g, width=7, height=4)    
    
    file_yandex = paste("measures-yandex-relation", "png", sep=".")
    filepath = file.path(save_path, file_yandex)
    ggsave(filepath, y, width=7, height=4)    
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
    plot_distances_synset(data, title, save_path)
    plot_distances_relation(data, title, save_path)
}

work_samples <- function() {
  print("Sample 01")
  work_sample("sample01.csv", "Ejemplo 1")
  print("Sample 02")
  work_sample("sample02.csv", "Ejemplo 2")
  print("Sample 03")
  work_sample("sample03.csv", "Ejemplo 3")
  print("Sample 04")
  work_sample("sample04.csv", "Ejemplo 4")
  print("Sample 05")
  work_sample("sample05.csv", "Ejemplo 5")
  print("Sample 06")
  work_sample("sample06.csv", "Ejemplo 6")
  print("Sample 07")
  work_sample("sample07.csv", "Ejemplo 7")
  print("Sample 08")
  work_sample("sample08.csv", "Ejemplo 8")
  print("Sample 09")
  work_sample("sample09.csv", "Ejemplo 9")
  print("Sample 10")
  work_sample("sample10.csv", "Ejemplo 10")
}
