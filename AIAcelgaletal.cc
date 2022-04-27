#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Acelgaletal1


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
typedef vector<int> VI;
typedef pair<int, Pos> Arco;
bool prim_bus = true;

vector<Pos> movimento_enanos(Pos& orig) {
     int f = 60, c = 60;
      vector<vector<int>> dist(f, vector<int>(c, 999999));
      vector<vector<Pos>> pred(f, vector<Pos>(c));
      vector<Pos> res;
      dist[orig.i][orig.j] = 0;
      priority_queue<pair<int, Pos>, vector<pair<int, Pos>>, greater<pair<int, Pos>> > Q;
      Q.push({0, orig});
      vector<vector<bool>> S(f, vector<bool>(c, false));
      //list<pair<int, Dir>> moviment;
      while (not Q.empty()) {
          Pos u = Q.top().second;
          Q.pop();
          //Dir res = moviment.front().second;
          //moviment.pop();
          if(not S[u.i][u.j]){
          if (cell(u).treasure) {
              //implementar funcion para reotrnar el ultimo movimento que he de hacer
            while(u != orig) {
                res.push_back(u);
                u = pred[u.i][u.j];
            }
              return res;
          }
          
          for (int i = 0; i < 8; ++i) {
              Pos v;
              //int cont = 1;
              v = u + Dir(i);
              int cost = 0;
              //int v_i = u_i + Dir(i).first;
              //int v_j = u_j + Dir(i).second;
              if(pos_ok(v)) {
                if(cell(v).type == Rock) {
                    cost = cell(v).turns;
                    if(dist[v.i][v.j] > dist[u.i][u.j] + cost) {
                    dist[v.i][v.j] = dist[u.i][u.j] + cost;
                    pred[v.i][v.j] = u;
                    Q.push({dist[v.i][v.j], v});
                    }
                }
                else if(cell(v).type == Cave) {
                    cost = 1;
                    if(dist[v.i][v.j] > dist[u.i][u.j] + cost) {
                    dist[v.i][v.j] = dist[u.i][u.j] + cost;
                    pred[v.i][v.j] = u;
                    Q.push({dist[v.i][v.j], v});
                }
                }
                else if(cell(v).type == Outside) {
                    cost = 1;
                    if(dist[v.i][v.j] > dist[u.i][u.j] + cost) {
                    dist[v.i][v.j] = dist[u.i][u.j] + cost;
                    pred[v.i][v.j] = u;
                    Q.push({dist[v.i][v.j], v});
                }
                }
                  //moviment.push({cont, Dir(i)});
              }
            }
            
            //++cont;
        }
      }
        return res;
}

void move_dwarves() {
        vector<Pos> cami;
        VI enanos = dwarves(me());
        int num_e = enanos.size();
        for (int i = 0; i < num_e; ++i) {
            int id = enanos[i];
            Pos p = unit(id).pos;
            Dir res = None;
            cami = movimento_enanos(p);
            int n = cami.size() - 1;
            Pos seg = cami[n];
            if(pos_ok(seg)) {
            //cerr << "Posicion enano: " << p << endl;
            //cerr << "Posicion sig: " << seg << endl;
            //bool fi = false;
            for(int j = 0; j < 8; ++j) {
                Pos aux = p + Dir(j);
                if(cell(aux).id != -1 and unit(cell(aux).id).type != Orc and unit(cell(aux).id).type != Troll and unit(cell(aux).id).player != me()) {
                    command(enanos[i], Dir(j));
                }
                if(aux == seg) {
                    res = Dir(j);
                    //fi = true;
                }
            }
            command(enanos[i], res);
            }
        }
}

//497, 

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
      move_dwarves();
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
