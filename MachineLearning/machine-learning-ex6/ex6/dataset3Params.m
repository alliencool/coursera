function [C, sigma] = dataset3Params(X, y, Xval, yval)
%DATASET3PARAMS returns your choice of C and sigma for Part 3 of the exercise
%where you select the optimal (C, sigma) learning parameters to use for SVM
%with RBF kernel
%   [C, sigma] = DATASET3PARAMS(X, y, Xval, yval) returns your choice of C and 
%   sigma. You should complete this function to return the optimal C and 
%   sigma based on a cross-validation set.
%

% You need to return the following variables correctly.
C = 1;
sigma = 0.3;

% ====================== YOUR CODE HERE ======================
% Instructions: Fill in this function to return the optimal C and sigma
%               learning parameters found using the cross validation set.
%               You can use svmPredict to predict the labels on the cross
%               validation set. For example, 
%                   predictions = svmPredict(model, Xval);
%               will return the predictions on the cross validation set.
%
%  Note: You can compute the prediction error using 
%        mean(double(predictions ~= yval))
%

error_opt = 1000000000;
C_opt = 0.01;
while C_opt <= 100
    sigma_opt = 0.01;
    while sigma_opt<=100
        model= svmTrain(X, y, C_opt, @(x1, x2) gaussianKernel(x1, x2, sigma_opt));
        predictions = svmPredict(model, Xval);
        error_pred = mean(double(predictions ~= yval));
        if error_pred < error_opt
            C = C_opt;
            sigma = sigma_opt;
            error_opt = error_pred;
        end
        sigma_opt = sigma_opt * 3;
    end
    C_opt = C_opt * 3;
end


% =========================================================================

end
