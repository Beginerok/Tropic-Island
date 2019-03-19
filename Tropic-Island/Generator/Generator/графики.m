fileID = fopen('resultR.txt','r');
formatSpec = '%f';
A = fscanf(fileID,formatSpec)
fclose(fileID);
plot(A)
figure;
hist(A)