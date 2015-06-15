# Sussna edge weight

sussna_edge_weight <- function(n, min, max) {
    r <- max - (max-min)/n
    #1/r
}

sussna_edge_weight_fixed <- function(n, min, max) {
    min + (max-min)/n
}

sussna <- function(n, min, max, depth, edge_weight) {
    w1 <- edge_weight(n, min, max)
    w2 <- edge_weight(n, min, max)
    (w1+w2)/(2*depth)
}

debug <- function(upto, min, max, depth) {
    print("Generate DEBUG graphs for Sussna semantic distance")
    n <- 1:upto
    sussna_ori_edge <- sapply(n, sussna_edge_weight, min, max) 
    sussna_fixed_edge <- sapply(n, sussna_edge_weight_fixed, min, max) 
    
    sussna <- sapply(n, sussna, min, max, depth, sussna_edge_weight)
    sussna_fixed <- sapply(n, sussna, min, max, depth, sussna_edge_weight_fixed)
    
    #par(pch=22, col="blue") # plotting symbol and color
    par(mfrow=c(1,2)) # all plots on one page
    
    heading = paste("Sussna (1993)") 
    plot(n, sussna, type="l", main=heading, xlab="n. relaciones", ylab="distancia")
    #lines(n, sussna, type="l")
    
    heading = paste("Modificado") 
    plot(n, sussna_fixed, type="l", main=heading, xlab="n. relaciones", ylab="distancia")
    #lines(n, sussna_fixed, type="l")
}
