# Work over results

library(data.table)
require(ggplot2)
library(reshape)

parse_sample <- function(file) {
    data <- data.table(read.csv(file=file, header=TRUE, sep="\t"))
}

plot_synset_tol <- function(data, title) {
    google <- subset(data, data$translator=="google")
    yandex <- subset(data, data$translator=="yandex")    
    
    x <- data[, synset.tolerance]
    y1 <- google[, similarity.value]
    y2 <- yandex[, similarity.value]
    df <- data.frame(tol=x, google=y1, yandex=y2)
    
    g <- ggplot(df, aes(tol)) +
        geom_line(aes(y=google, colour="Google")) +
        geom_line(aes(y=yandex, colour="Yandex")) +
        scale_colour_manual("Traductores", 
                            breaks = c("Google", "Yandex"),
                            values = c("red", "blue"))
    g <- g + ylab("Similaridad") + xlab("Tolerancia entre conceptos")
    g <- g + labs(title=title)
    g
}

work_sample <- function(file, title) {
    data <- parse_sample(file)
    plot_synset_tol(data, title)
}

