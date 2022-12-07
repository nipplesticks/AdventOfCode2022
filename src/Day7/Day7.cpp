#include "Day7.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <array>
#include <deque>
#include <assert.h>

const std::string path = "src/Day7/";
constexpr size_t SYSTEM_SIZE = 70000000;
constexpr size_t UPDATE_SIZE = 30000000;

struct Node
{
  Node* parent_p = nullptr;
  std::string name = "";
  bool isDir = false;
  size_t size = 0;
  std::vector<Node> subNodes;
};

Node* root_p = nullptr;
std::vector<size_t> candidates;

void _update(Node* ptr_p)
{
  for (auto& p : ptr_p->subNodes)
  {
    if (p.isDir)
      _update(&p);
    ptr_p->size += p.size;
  }
}

void _tree(Node* ptr_p, int subLevel)
{
  for (int i = 0; i < subLevel * 2; i++)
  {
    std::cout << " ";
  }
  std::cout << "- ";
  std::cout << ptr_p->name;
  if (ptr_p->isDir)
    std::cout << "/ (dir, contains=" << ptr_p->size << ")";
  else
    std::cout << " (file, size=" << ptr_p->size << ")";
  std::cout << std::endl;
  for (auto& n : ptr_p->subNodes)
    _tree(&n, subLevel + 1);
}

size_t _totalSizeOfFoldersContainingAtMost(Node* ptr_p, const size_t& size)
{
  size_t s = 0;
  if (ptr_p->isDir)
  {
    if (ptr_p->size < size)
      s += ptr_p->size;
    for (auto& n : ptr_p->subNodes)
    {
      s += _totalSizeOfFoldersContainingAtMost(&n, size);
    }
  }
  return s;
}

void _findCandidates(Node* ptr_p, const size_t& minSize)
{
  if (ptr_p->isDir)
  {
    if (ptr_p->size >= minSize)
      candidates.push_back(ptr_p->size);
    for (auto& n : ptr_p->subNodes)
    {
      _findCandidates(&n, minSize);
    }
  }
}

void Day7::Run()
{
  root_p = new Node;
  root_p->name = "/";
  root_p->isDir = true;

  Node* current_p = nullptr;

  std::ifstream input(path + "Input.txt");

  if (input)
  {
    std::string line = "";
    bool lastWasLS = false;
    while (std::getline(input, line))
    {
      std::stringstream ss(line);
      std::string first;
      ss >> first;

      if (first == "$") // is a command
      {
        lastWasLS = false;
        std::string command;
        ss >> command;

        if (command == "cd")
        {
          std::string dir;
          ss >> dir;
          if (dir == "/")
            current_p = root_p;
          else if (dir == "..")
          {
            current_p = current_p->parent_p;
          }
          else
          {
            for (auto& n : current_p->subNodes)
              if (n.name == dir)
              {
                current_p = &n;
                break;
              }
          }
        }
        else if (command == "ls")
        {
          lastWasLS = true;
        }
        else
        {
          assert(false);
        }
      }
      else if (lastWasLS)
      {
        Node n;
        ss >> n.name;
        n.parent_p = current_p;
        if (first == "dir")
        {
          n.isDir = true;
        }
        else
        {
          n.size = std::atoi(first.c_str());
        }
        current_p->subNodes.push_back(n);
      }
      else
      {
        assert(false);
      }
    }

    _update(root_p);
    //_tree(root_p, 0);
    //size_t totSize = _totalSizeOfFoldersContainingAtMost(root_p, 100000);
    std::cout << "Total System size: " << SYSTEM_SIZE << std::endl;
    std::cout << "Size on disk: " << root_p->size << std::endl;
    std::cout << "Free size: " << SYSTEM_SIZE - root_p->size << std::endl;
    std::cout << "Update size: " << UPDATE_SIZE << std::endl;
    std::cout << "Need to delete folder too free up: " << UPDATE_SIZE - (SYSTEM_SIZE - root_p->size) << std::endl;
    size_t needToDelete = UPDATE_SIZE - (SYSTEM_SIZE - root_p->size);
    _findCandidates(root_p, needToDelete);
    std::sort(candidates.begin(), candidates.end());
    std::cout << "found " << candidates.size() << " candidates\n";
    std::cout << "size freed: " << candidates.front() << std::endl;

    std::ofstream output(path + "Output.txt");
    if (output)
    {
      output << candidates.front();
      output.close();
    }

    //std::cout << candidates.front() << std::endl;

    input.close();
  }
}
