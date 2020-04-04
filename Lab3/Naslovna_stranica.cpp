#include<iostream>
#include<cstring>
using namespace std;
//-------------------------------------- CATEROGY
class Category {
private:
    char name[20];
public:
    Category() {
        strcpy(this->name,"unnamed");
    }
    Category(char *name) {
        strcpy(this->name,name);
    }
    ~Category() {}
    void print() {
        cout<<"Category: "<<this->name<<endl;
    }
};
//-------------------------------------- NEW ARTICLE
class NewsArticle {
private:
    Category category;
    char title[30];
public:
    NewsArticle() {
        strcpy(this->title,"untitled");
    }
    NewsArticle(Category category, char *title) {
        this->category=category;
        strcpy(this->title,title);
    }
    NewsArticle(Category category) {
        this->category=category;
        strcpy(this->title,"untitled");
    }
    ~NewsArticle() {}
    void print() {
        cout<<"Article title: "<<this->title<<endl;
        this->category.print();
    }
};
//---------------------------------------FRONT PAGE
class FrontPage {
private:
    NewsArticle article;
    float price;
    int editionNumber;
public:
    FrontPage() {
        this->price=0;
        this->editionNumber=0;
    }
    FrontPage(NewsArticle article, float price, int editionNumber) {
        this->article=article;
        this->price=price;
        this->editionNumber=editionNumber;
    }
    FrontPage(NewsArticle article, float price) {
        this->article=article;
        this->price=price;
        this->editionNumber=0;
    }
    ~FrontPage() {}
    void print() {
        cout<<"Price: "<<this->price<<", Edition number: "<<this->editionNumber<<endl;
        this->article.print();
    }
};
int main() {
    char categoryName[20];
    char articleTitle[30];
    float price;
    int editionNumber;
    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        int iter;
        cin >> iter;
        while (iter > 0) {
            cin >> categoryName;
            cin >> articleTitle;
            cin >> price;
            cin >> editionNumber;
            Category category(categoryName);
            NewsArticle article(category, articleTitle);
            FrontPage frontPage(article, price, editionNumber);
            frontPage.print();
            iter--;
        }
    } else if (testCase == 2) {
        cin >> categoryName;
        cin >> price;
        cin >> editionNumber;
        Category category(categoryName);
        NewsArticle article(category);
        FrontPage frontPage(article, price, editionNumber);
        frontPage.print();
    }// test case 3
    else if (testCase == 3) {
        cin >> categoryName;
        cin >> articleTitle;
        cin >> price;
        Category category(categoryName);
        NewsArticle article(category, articleTitle);
        FrontPage frontPage(article, price);
        frontPage.print();
    } else {
        FrontPage frontPage = FrontPage();
        frontPage.print();
    }
    return 0;
}