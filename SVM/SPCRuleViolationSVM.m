%% Train Multi-Class Support Vector Machine Classifier
% ----------------------------------------------------------------------
% Reference: https://www.mathworks.com/help/stats/classificationecoc-class.html#bvc1ldw-1
% https://www.mathworks.com/help/stats/templatesvm.html
% https://www.mathworks.com/help/stats/fitcecoc.html#outputarg_Mdl

%Load data for Font Recognition

load SPC_Train_In
load SPC_Train_Out

%Load training data
X = SPC_Train_In;
Y = SPC_Train_Out;

%Build class labels
labels = [1;2;3;4;5;6;]
Y = Y(:,2:7) * labels 

load SPC_Test_In
load SPC_Test_Out

Xt = SPC_Test_In;
Yt = SPC_Test_Out;

%Build class labels
Yt = Yt(:,2:7) * labels

ClassLabels = [0;1;2;3;4;5;6;]

% CASE 1
% Train an error-correcting output codes (ECOC) multiclass model using support vector machine (SVM)
% binary learners. 
% Train an ECOC multiclass model using the default options.
%Mdl = fitcecoc(X,Y)
% |Mdl| is a |ClassificationECOC| model.  By default, |fitcecoc| uses SVM binary learners, and uses
% a one-versus-one coding design. You can access |Mdl| properties using dot notation.

%testSVMClassifier(Mdl, Xt, Yt, ClassLabels)

% CASE 2
% Train a classifier
% This code specifies all the classifier options 
plotname = 'SVM with Gaussian Kernel Fnc'
template = templateSVM(...
    'KernelFunction', 'Gaussian', ...
    'PolynomialOrder', [], ...
    'KernelScale', 5, ...
    'BoxConstraint', 10, ...
     'Nu', 0.1, ...
    'Standardize', false);

responseName = 'Font';

Mdl = fitcecoc(X,Y,'Learners',template,'ResponseName',responseName,'ClassNames',ClassLabels)

testSVMClassifier(Mdl, Xt, Yt, ClassLabels, plotname)


% CASE 2
% Train a classifier
% This code specifies all the classifier options 
plotname = 'SVM with Polynomial Kernel Fnc'
template = templateSVM(...
    'KernelFunction', 'polynomial', ...
    'PolynomialOrder', [3], ...
    'KernelScale', 5, ...
    'BoxConstraint', 10, ...
    'Standardize', false);

responseName = 'Font';

Mdl = fitcecoc(X,Y,'Learners',template,'ResponseName',responseName,'ClassNames',ClassLabels)

testSVMClassifier(Mdl, Xt, Yt, ClassLabels, plotname)


function [trainedClassifier, validationAccuracy] = testSVMClassifier(Mdl, Xt, Yt , ClassLabels, plotname)
% Display the coding design matrix.
Mdl.ClassNames
CodingMat = Mdl.CodingMatrix

% A one-versus-one coding design on three classes yields three binary learners.  Columns of
% |CodingMat| correspond to learners and rows correspond to classes.  The class order corresponds to
% the order in |Mdl.ClassNames|. For example, |CodingMat(:,1)| is |[1; -1; 0]|, and indicates that
% the software trains the first SVM binary learner using all observations 


% You can access each binary learner using cell indexing and dot notation.
Mdl.BinaryLearners{1}                % The first binary learner
Mdl.BinaryLearners{1}.SupportVectors % Support vector indices

% Compute the in-sample classification error.
isLoss = resubLoss(Mdl)

% Predict the Test data classes based on Trained model
%label = predict(Mdl,Xt)
[label,score] = predict(Mdl,Xt)
tabulate(categorical(Yt))
table(Yt(1:10),label(1:10),score(1:10,2),'VariableNames',...
    {'TrueLabel','PredictedLabel','Score'})

[n,p] = size(Xt)
nLabels = numel(ClassLabels)


% Convert the integer label vector to a class-identifier matrix.
[~,grpOOF] = ismember(label,ClassLabels); 
oofLabelMat = zeros(nLabels,n); 
idxLinear = sub2ind([nLabels n],grpOOF,(1:n)'); 
oofLabelMat(idxLinear) = 1; % Flags the row corresponding to the class 
[~,grpY] = ismember(Yt,ClassLabels); 
YMat = zeros(nLabels,n); 
idxLinearY = sub2ind([nLabels n],grpY,(1:n)'); 
YMat(idxLinearY) = 1; 

% Plot the confusion matrix
ConfMat = confusionmat(Yt,label);
figure;
plotconfusion(YMat,oofLabelMat, plotname);

h = gca;
%h.XTickLabel = [num2cell(ClassLabels); {''}];
%h.YTickLabel = [num2cell(ClassLabels); {''}];

validationAccuracy = 1 - resubLoss(Mdl, 'LossFun', 'ClassifError');
validationAccuracy
end
