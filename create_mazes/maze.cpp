/* Your code here! */
#include "maze.h"

SquareMaze::SquareMaze(){

}

void SquareMaze::makeMaze(int width, int height){
  down.clear();
  right.clear();
  width_ = width;
  height_ = height;
  for(int i =0; i<width_*height_; i++){
    down.push_back(false);
    right.push_back(false);
  }
  DisjointSets circle;
  circle.addelements(width_*height_);

  int flag = 0;
//  std::cout<< "1"<<std::endl;
  while(flag < width_*height_-1){
    //std::cout<<"flag:"<< flag<<std::endl;
    int x = rand() % width_;
    int y= rand() % height_;
    //remove dowm wall;
    if(rand()%2 == 0){
      //std::cout<< "2"<<std::endl;
      if(y >= height_-1) continue;
      int a = circle.find(x+y*width_);
      int b = circle.find(x+(y+1)*width_);
      // std::cout<< "4"<<std::endl;
        // std::cout<< a<<" "<<b<<std::endl;
      if( !down[x+y*width_] && a != b){
      //  std::cout<< "6"<<std::endl;
          down[x+y*width_] = true;
          circle.setunion(a,b);
          flag ++;
      }
    } else {//remove right wall;
      //std::cout<< "3"<<std::endl;
      if(x >= width_-1) continue;
      int a = circle.find(x+y*width_);
      int b = circle.find(x+1+y*width_);
      if(x < width_-1 && !right[x+y*width_] && a != b){
          right[x+y*width_] = true;
          circle.setunion(a,b);
          flag ++;
        }
    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
  if (x < 0 || x >= width_ || y < 0 || y >= height_)
    return false; // <0????
  if(dir == 0)
    return right[x+y*width_];
  if(dir == 1)
    return down[x+y*width_];
  if(dir == 2){
    if(x == 0)
      return false;
    return right[x-1+y*width_];
  }
  if(dir == 3) {
    if(y == 0)
      return false;
    return down[x+(y-1)*width_];
  }
  return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
  if(x >= width_ || y >= height_) return;
  if(dir == 0){
    right[x+y*width_] = !exists;
  }
  if(dir == 1){
    down[x+y*width_] = !exists;
  }
}

std::vector<int> SquareMaze::solveMaze(){

  std::vector<int> curr;
  std::vector<int> result(0);

  std::vector<std::vector<bool>> visited;
  for(int i =0 ; i < width_; i++){
    std::vector<bool> line;
    visited.push_back(line);
    for(int j = 0; j < height_;j++) {
      /* code */
      visited[i].push_back(false);
    }
  }

  dfs(0,0,visited,curr,result,width_ +1, 0);
  // std::cout<< result.size()<<std::endl;
  // for(int op: result){
  //   std::cout<<op;
  // }
  //aqsstd::cout<<longest.size()<<std::endl;

  if(!longest.empty())
    longest.erase(longest.begin());

  return longest;
}

void SquareMaze::dfs(int x, int y, std::vector<std::vector<bool>>& visited,
          std::vector<int>& curr, std::vector<int>& result, int rx,int op){
      //std::cout<<x <<" "<< y<<std::endl;
  curr.push_back(op);
  if(y == height_ - 1){
      if (curr.size() > longest.size()){
              //std::cout<<"len: "<<x<<" "<<curr.size()<<" "<<result.size()<<std::endl;
        longest.clear();
        for(int elem: curr){
          longest.push_back(elem);
        }
        rx = x;
      } else if(curr.size() ==  longest.size() && x < rx){
          //  std::cout<<"len: "<<x<<" "<<curr.size()<<" "<<result.size()<<std::endl;
        longest.clear();
        for(int elem: curr){
          longest.push_back(elem);
        }
        rx = x;
      }
  }

  visited[y][x] =true;
  //std::cout<< "in "<<y<<" "<<x<<std::endl;
  int dx[] = {1,0,-1,0};
  int dy[] = {0,1,0,-1};

  // for(int op: curr){
  //   std::cout<<op;
  // }
  for(int i = 0; i < 4; i++){
    int nx  = x + dx[i], ny = y + dy[i];
    //std::cout<<"in "<<x << " " << y << " go to"<<nx<<" "<<ny<<std::endl;

    if(nx< 0 || nx >= width_ || ny <0||ny >=height_||
      !canTravel(x, y, i)|| visited[ny][nx]) continue;

    //std::cout<< "pass go to"<<nx<<" "<<ny << " "<<i<<std::endl;
    dfs(nx, ny, visited,curr, result,rx,i);
  }

  curr.pop_back();
}
//
PNG * SquareMaze::drawMaze() const{
    PNG* canvas= new PNG(width_ * 10 + 1, height_ * 10 + 1);
    //left
    for (int i = 0; i < height_ * 10 + 1; i++) {
      HSLAPixel& pixel = canvas->getPixel(0, i);
      pixel.l = 0.0;
    }
    //top
    for (int i = 10; i < width_ * 10 + 1; i++) {
      HSLAPixel& pixel = canvas->getPixel(i, 0);
      pixel.l = 0.0;
    }

    for (int x = 0; x < width_; x++) {
      for (int y = 0; y < height_; y++) {
        if (!right[x + y * width_]) {
          for (int k = 0; k < 11; k++) {
            HSLAPixel& pixel = canvas->getPixel(10 * x + 10, 10 * y + k);
            pixel.l = 0.0;
          }
        }
        if (!down[x + y * width_]) {
          //std::cout<<"down "<<x << " " << y <<std::endl;
          for (int k = 0; k < 11; k++) {
            HSLAPixel& pixel = canvas->getPixel(10 * x + k, 10 * y + 10);
            pixel.l = 0.0;
          }
        }
      }
    }
    return canvas;
}

PNG * SquareMaze::drawCreativeMaze() const{
    PNG* canvas= new PNG(width_ * 10 + 1, height_ * 10 + 1);
    //left
    // for (int i = 0; i < height_ * 10 + 1; i++) {
    //   HSLAPixel& pixel = canvas->getPixel(0, i);
    //   pixel.l = 0.0;
    // }
    //top
    for (int i = 10; i < width_ * 10 + 1; i++) {
      HSLAPixel& pixel = canvas->getPixel(i, 0);
      pixel.l = 0.0;
    }

    for (int x = 0; x < width_; x++) {
      for (int y = 0; y <=x; y++) {
        if(y == x && x >=1  ){
          for (int k = 0; k < 11; k++) {
            HSLAPixel& pixel = canvas->getPixel(10 * (x-1) , 10 * (y-1) +k );
            pixel.l = 0.0;
          }
          for (int k = 0; k < 11; k++) {
            HSLAPixel& pixel = canvas->getPixel(10 * x + k, 10 * y + 10);
            pixel.l = 0.0;
          }
        }
        if (!right[x + y * width_]) {
          for (int k = 0; k < 11; k++) {
            HSLAPixel& pixel = canvas->getPixel(10 * x + 10, 10 * y + k);
            pixel.l = 0.0;
          }
        }
        if (!down[x + y * width_]) {
          //std::cout<<"down "<<x << " " << y <<std::endl;
          for (int k = 0; k < 11; k++) {
            HSLAPixel& pixel = canvas->getPixel(10 * x + k, 10 * y + 10);
            pixel.l = 0.0;
          }
        }
      }
    }
    return canvas;
}


PNG * SquareMaze::drawMazeWithSolution() {
   PNG* canvas = drawMaze();
     std::vector<int> ops = solveMaze();
     int x = 5;
     int y = 5;
     for (int dir: ops) {
       switch (dir) {
         case 0/* value */:
           for (int i = 0; i < 10; i++) {
             HSLAPixel& pixel = canvas->getPixel(x, y);
             pixel.h = 0;
             pixel.s = 1;
             pixel.l = 0.5;
             x += 1;
           }
           break;
         case 1/* value */:
           for (int i = 0; i < 10; i++) {
             HSLAPixel& pixel = canvas->getPixel(x, y);
             pixel.h = 0;
             pixel.s = 1;
             pixel.l = 0.5;
             y += 1;
           }
           break;
         case 2/* value */:
           for (int i = 0; i < 10; i++) {
             HSLAPixel& pixel = canvas->getPixel(x, y);
             pixel.h = 0;
             pixel.s = 1;
             pixel.l = 0.5;
             x -= 1;
           }
           break;
         case 3/* value */:
           for (int i = 0; i < 10; i++) {
             HSLAPixel& pixel = canvas->getPixel(x, y);
             pixel.h = 0;
             pixel.s = 1;
             pixel.l = 0.5;
             y -= 1;
           }
           break;
         }
      }

     HSLAPixel& p = canvas->getPixel(x, y);
     p.h = 0.0;
     p.s = 1.0;
     p.l = 0.5;
     p.a = 1.0;

     x -= 4;
     y += 5;
     for (int i = 0; i < 9; i++) {
       HSLAPixel& pixel = canvas->getPixel(x, y);
       pixel.l = 1.0;
       pixel.a = 1.0;
       x += 1;
     }
     return canvas;
   }
