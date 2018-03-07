% Written by Om Soni

load SPC_Train_In
load SPC_Train_Out

%Load training data
X = SPC_Train_In;
Y = SPC_Train_Out;

%Build class labels
Y = logical(Y(:,1))
labels = [0;1;]

load SPC_Test_In
load SPC_Test_Out

Xt = SPC_Test_In;
Yt = SPC_Test_Out;

%Build class labels
Yt = logical(Yt(:,1))

Mdl = fitcsvm(X,Y,'Standardize',true,'KernelFunction','Gaussian',...
     'PolynomialOrder', [], ...
    'KernelScale', 5, ...
    'BoxConstraint', 10);

classOrder = Mdl.ClassNames;


sv = Mdl.SupportVectors;
rng(1);
CVMdl = crossval(Mdl);
classLoss = kfoldLoss(CVMdl)

%Predict response for observations not used for training 
[~,scorePred] = kfoldPredict(CVMdl);
outlierRate = mean(scorePred<0)

% Fit posterior probabilities
mdlSVM = fitSVMPosterior(Mdl);
[label,score] = resubPredict(mdlSVM);
table(Y(1:10),label(1:10),score(1:10,2),'VariableNames',...
    {'TrueLabel','PredictedLabel','Score'})


[Xsvm,Ysvm,Tsvm,AUCsvm] = perfcurve(Y,score(:,mdlSVM.ClassNames),'true');
figure(1);
plot(Xsvm,Ysvm, 'g','LineWidth',2);
xlabel('False positive rate')
ylabel('True positive rate')
title('ROC (Resub) for Classification by Two Class SVM: Gaussian Kernel')


[~,score] = predict(Mdl,Xt);
[Xsvm,Ysvm,Tsvm,AUCsvm] = perfcurve(Yt,score(:,Mdl.ClassNames),'true');
figure(2);
plot(Xsvm,Ysvm, 'g','LineWidth',2);
xlabel('False positive rate')
ylabel('True positive rate')
title('ROC (Test) for Classification by Two Class SVM: Gaussian Kernel')
