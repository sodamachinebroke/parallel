# parallel

## Task info
My assignment will utilize parallelization in image processing.
It will receive an image and apply a filter to it. First with a sequential method and then using OpenMP.
Also will include performance tests with different resolution pictures and different filters.
The program will go and apply a filter pixel by pixel. This can be parallelized.
Parallel thread number will be variable, or "smart", depending on workload heavinness. Depends on if i have time.
The program should have three versions, including one based on POSIX thread manipulation, one based on OpenMP and the third version will utilize MPI.

## Experiences so far
So far it works in sequential mode and using OMP parallelization.
I have two images in the filterApplicator/images folder. One of them being a very large file of ~50MB and the other is slightly smaller at ~4MB.
The program can apply two filters: a greyscaler and a negator??? negativizer?? grammar. Anyway it does that quite effectively.  
However well it runs, it loses exactly 84bytes of data, regardless of file size which is curious.

I have made it work with both POSIX threads and OpenMPI. It was a struggle, but i won.  
Also found a large image but it's 2.5GB in size and i don't think GitHub would like that. However, we are here to experiment, so let's try.  


I would like to find a very very large BMP image. Think GigaBytes and then see what the program does, because both of my machines run on SSDs. Although i could use an old computer at home, from around 2002. That should have some trouble converting said images. Great idea, thank me!  
I found said image.
