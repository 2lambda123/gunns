# Start with 'gunns_unloaded_or8' image.
FROM gunns_unloaded_or8

# Clone GUNNS
WORKDIR /home
RUN git clone https://github.com/nasa/gunns.git

# Make the GUNNS compiled libs
WORKDIR gunns/lib/test
RUN make
WORKDIR ../no_trick
RUN make
WORKDIR ../trick
RUN make
WORKDIR ../trick_if
RUN make
WORKDIR ../..
