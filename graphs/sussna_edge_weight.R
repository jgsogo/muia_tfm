# Sussna edge weight
require(ggplot2)
library(reshape)
source("multiplot.R")

sussna_edge_weight <- function(n, min, max) {
    r <- max - (max-min)/n
    #1/r
}

sussna_edge_weight_fixed <- function(n, min, max) {
    r <- max - (max-min)/n
    1/r
}

sussna <- function(n, min, max, depth, edge_weight) {
    w1 <- edge_weight(n, min, max)
    w2 <- edge_weight(n, min, max)
    (w1+w2)/(2*depth)
}

debug <- function(upto = 15, min = 1, max = 2) {
    print("Generate DEBUG graphs for Sussna semantic distance")
    n <- 1:upto

    sussna_ori <- sapply(n, sussna, min, max, 1, sussna_edge_weight)
    sussna_fixed <- sapply(n, sussna, min, max, 1, sussna_edge_weight_fixed)

    sussna_ori_10 <- sapply(n, sussna, min, max, 10, sussna_edge_weight)
    sussna_fixed_10 <- sapply(n, sussna, min, max, 10, sussna_edge_weight_fixed)
    
    # Formulación en Sussna
    df <- data.frame(n, sussna_ori, sussna_ori_10)
    colnames(df) <- c("n", "depth = 1", "depth = 10")
    
    df <- melt(df, id=c("n"))
    p1 <- ggplot(df) + geom_line(aes(n, y=value, colour=variable)) +
      ylab("Distancia") + xlab("Núm. conexiones") +
      labs(title="Formulación en Sussna (1993)") +
      theme(legend.position="none")
    
    # Corrección propuesta
    df <- data.frame(n, sussna_fixed, sussna_fixed_10)
    colnames(df) <- c("n", "depth = 1", "depth = 10")
    
    df <- melt(df, id=c("n"))
    p2 <- ggplot(df) + geom_line(aes(n, y=value, colour=variable)) +
      ylab("Distancia") + xlab("Núm. conexiones") +
      labs(title="Formulación propuesta") +
      theme(legend.position="none")
    
    multiplot(p1, p2, cols=2)
}
