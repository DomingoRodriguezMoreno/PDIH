install.packages('tuneR', dep=TRUE)
install.packages('seewave', dep=TRUE)
install.packages('soundgen', dep=TRUE)

library(tuneR)
library(seewave)
library(soundgen)
library(audio)

# establecer el path concreto en cada caso a la carpeta de trabajo
setwd("C:/Users/domin/Desktop/PDIH/P4")

gato  <- readMP3('gato.mp3')
gato
oveja <- readWave('oveja.wav')
oveja

str(gato)
str(oveja)

plot( extractWave(gato, from = 1, to = 393984))
plot( extractWave(oveja, from = 1, to = 19764) )

union <- pastew(gato, oveja, output="Wave")
str(union)

plot( extractWave(union, from = 1, to = 44100) )

f <- union@samp.rate

listen(union,f=f)

filtro <- bwfilter(union, f=f, channel = 1, n=1, from = 3000, to = 20000, bandpass = TRUE, listen = FALSE, output = "Wave")

writeWave(filtro, file.path("mezcla.wav") )


perro <- readWave('perro.wav')
perro

str(perro)

plot( extractWave(perro, from = 1, to = 44100) )

perroEco <- echo(perro, f=159732, amp = c(0.8,0.4,0.2), delay = c(1,2,3), output = "Wave")

perroEco

listen(perroEco,f=159732)


plot( extractWave(perroEco, from = 1, to = 638928) )

perroEcoReves <- revw(perroEco, f=159732, output = "Wave")

str(perroEcoReves)

listen(perroEcoReves,f=159732)

plot( extractWave(perroEcoReves, from = 1, to = 638928) )

writeWave(perroEcoReves, file.path("alreves.wav") )

