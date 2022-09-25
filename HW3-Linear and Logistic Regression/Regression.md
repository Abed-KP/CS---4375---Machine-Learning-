---
title: "Regression"
output:
  html_notebook: default
  pdf_document: default
---

### Team: Abed Ahmed (ASA190005) & Dylan Kapustka (DLK190000)
### Date: 09/25/2022
### HomeWork 3 - Regression

# Linear Regression

Linear Regression is a Machine Learning algorithm based on the mathematics concept that allows us
to predict one dependent target variable, based on one or more independent variables.

In very simple terms, if we look at the equation **y = mx + b**, With target **y** and independant given variable **x**, Linear Regression will estimate values **m** and **b** allowing us to plug them in and estimate target **y** 
for any **x** .

In this notebook, we will look at a data set describing various attributes of Anime and Manga, and build some linear
models with them.

Data Source: https://www.kaggle.com/datasets/hernan4444/anime-recommendation-database-2020

### Pros of Linear Regression
- Easy To implement and interpret
- Easy to identify Use cases for by spotting potential correlations in data
- Has some techniques to avoid over fitting

### Cons of Linear Regression
- Assumes relationship between independent and dependent variables. Assumes there is a straight line.
- Does not provide a complete description of relationships among variables. 

### The below chunk does the following

- Imports and cleans data
- Splits into 80/20 train/test
- Explores the data
- Plots two informative graphs


``` {r}

data <- Anime.Data
data = dplyr::select(data, -c('Japanese.name','Score.1':'Score.10'))
data <- na.omit(data)

set.seed(2)
library(caTools)

split <- sample.split(data,SplitRatio=0.8)
train <- subset(data, split==TRUE)
test <- subset(data,split==FALSE)

names(train)
head(train)
summary(train)
mean(train$Score)
median(train$Score)

plot(train$Score~train$Ranked,xlab="Ranked",ylab="Score")
abline(lm(train$Score~train$Ranked),col="red")

plot(train$Score~train$Episodes,xlab="Episodes",ylab="Score")
abline(lm(train$Score~train$Episodes),col="blue")

```

### This chunk will
- Build a simple linear model of the data
- outputs the summary

``` {r}
lm1 <- lm(Score~Ranked,data=train)
summary(lm1)
```


### Summary of Simple Linear Model

The summary function in R has outputted a number of things.

- A **formula** that shows that we are modelling the score as a function of Rank
- **Residuals** that show the difference between what the model predicted and the actual value of **y**
- **Coefficients**
- The **Estimates** where the intercept tells us the value when all other features are 0. For the other features, the estimates give us the expected change in the response due to a unit change in the feature.
- **Standard Error** which allows us to construct marginal confidence intervals for the estimate of that particular feature.
- **t-value** which tells us about how far our estimated parameter is from the hypothesized 0 value.
- The **p-value** for the individual coefficient, which is the level of marginal significance within a statistical hypothesis test, representing the probability of the occurrence of a given event.
- The Residual Standard Error which gives the standard deviation of the residuals, and tells us about how large the prediction error is.
- **Multiple and Adjusted R^2^** which tell us what proportion of the variance is explained by out model
- **F-Stats** Which is the ratio of two variances

### The next chunk will output various residuals plots

``` {r}
par(mfrow=c(2,2))
plot(lm1)
```


### Explanation of Residual plot for the Simple Linear Model

For starters, the residuals max is relatively low. This can be verified by the fact that the original plot of the
linear model showed a very strong linear trend. Also, in a residual plot, we want there to be a spread of values
above and below the line that are close to even. In this residual plot however, many fall exactly on that lne which shows an almost direct causation relationship between ranking and Score, which implies that Score is directly derived
from the Rank.

### Next, we create a multiple linear model using Number of Episodes, Rank, and target Score

```{r}
lm2 <- lm(Score~Dropped+Episodes,data=train)
summary(lm2)
par(mfrow=c(2,2))
plot(lm2)
```


### Next, we create a second multiple linear model using Popularity, Rank, and target Score

```{r}
lm3 <- lm(Score~Watching+Popularity,data=train)
summary(lm3)
par(mfrow=c(2,2))
plot(lm3)
```

### Next, let us use our models and make perdictions

```{r}
pred1 <- predict(lm1,newdata=test)
pred2 <- predict(lm2,newdata=test)
pred3 <- predict(lm3,newdata=test)

cor1 <- cor(pred1,test$Score)
mse1 <- mean((pred1 - test$Score)^2)
rmse1 <- sqrt(mse1)
print(paste("Correlation of the first model: ", cor1))
print(paste("mse of the first model: ", mse1))
print(paste("rmse of the first model: ", rmse1))


cor2 <- cor(pred2,test$Score)
mse2 <- mean((pred2 - test$Score)^2)
rmse2 <- sqrt(mse2)
print(paste("Correlation of the second model: ", cor2))
print(paste("mse of the second model: ", mse2))
print(paste("rmse of the second model: ", rmse2))

cor3 <- cor(pred3,test$Score)
mse3 <- mean((pred3 - test$Score)^2)
rmse3 <- sqrt(mse3)
print(paste("Correlation of the third model: ", cor3))
print(paste("mse of the third model: ", mse3))
print(paste("rmse of the third model: ", rmse3))
```

 
## Analysis of models
The first model showed Score as a function of Rank.
The second model showed Score as a function of number of existing episodes + how many people dropped the show.
The third model showed Score as a function  of user rated popularity + individuals currently watching the show.

Ultimately, the simple linear model performed best out of the 3. Despite the latter two providing a multi-varied
analysis using multiple attributes, the single best predictor was proven to be the ranking of each anime, as the plots and correlation showed than rank directly influences the score it received.

The first simple model had the greatest correlation sitting at 0.97, as compared to the second with 0.23 and third, 0.56. We want this number to be as close to -1/1 as possible.

The rmse of the first was also the least, which shows we are less off using the first model than the other two. The first model was off by an average of 0.14, while the other two were off by 0.59 and 0.49 respectively.

Ultimately, I believe the reason for this was simply the chose attributes. It was interesting though how the 
third model performed, which showed a semi-decent correlation with popularity, people currently watching, and Score.
