#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Subsection 
{
public:
    string name;
    Subsection(string name) : name(name) {}
    void print(int level) const 
	{
        cout << string(level * 2, ' ') << "Subsection: " << name << endl;
    }
};

class Section 
{
public:
    string name;
    vector<Subsection> subsections;

    Section(string name) : name(name) {}

    void addSubsection(const Subsection& subsection) {
        subsections.push_back(subsection);
    }

    void print(int level) const {
        cout << string(level * 2, ' ') << "Section: " << name << endl;
        for (const auto& subsection : subsections) {
            subsection.print(level + 1);
        }
    }
};

class Chapter 
{
public:
    string name;
    vector<Section> sections;

    Chapter(string name) : name(name) {}

    void addSection(const Section& section) {
        sections.push_back(section);
    }

    void print(int level) const {
        cout << string(level * 2, ' ') << "Chapter: " << name << endl;
        for (const auto& section : sections) {
            section.print(level + 1);
        }
    }
};

class Book 
{
public:
    string name;
    vector<Chapter> chapters;

    Book(string name) : name(name) {}

    void addChapter(const Chapter& chapter) {
        chapters.push_back(chapter);
    }

    void print() const {
        cout << "Book: " << name << endl;
        for (const auto& chapter : chapters) {
            chapter.print(1);
        }
    }
};

int main() 
{
    // Create the book
    Book book("Programming Basics");

    // Create chapters and sections
    Chapter chapter1("Introduction");
    Section section1("Overview");
    section1.addSubsection(Subsection("What is Programming?"));
    section1.addSubsection(Subsection("History of Programming"));
    chapter1.addSection(section1);

    Chapter chapter2("Variables");
    Section section2("Types of Variables");
    section2.addSubsection(Subsection("Integer"));
    section2.addSubsection(Subsection("String"));
    chapter2.addSection(section2);

    // Add chapters to the book
    book.addChapter(chapter1);
    book.addChapter(chapter2);

    // Print the book structure
    book.print();

    return 0;
}

