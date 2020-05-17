//--Wesley Burlani

#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

enum TECLAS { CIMA, BAIXO, ESQUERDA, DIREITA };
ALLEGRO_BITMAP *aster = NULL;
int x = 5, y = 5, x1 = 40, y1 = 40;
int highscore;
int i;
int person = 0;

//------------------Funções-----------
bool colide(int O_x, int O_y) {
  if (!(x > O_x || (x + x1) < (O_x + 9) || y > O_y || (y + y1) < (O_y + 9)))
    return true;
  return false;
}

void desenha(int O_x, int O_y) {
  al_draw_bitmap(
      aster, O_x - 2, O_y - 2,
      0); /*al_draw_filled_rectangle(O_x,O_y,O_x+9,O_y+9,al_map_rgb(255,255,255));*/
}

//-------------Inicio da Main----------
int main() {
  //------------variaveis----------------
  const int LARGURA_T = 640, ALTURA_T = 480;
  int flag = 0, c_x = 200, c_y = 30, zaza_x = -5, zaza_y = -5, soum = 0;
  bool fim = false, sair = false, exit = false,
       teclas[] = {false, false, false, false};
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_BITMAP *imagem = NULL;
  ALLEGRO_BITMAP *fefe = NULL;
  ALLEGRO_BITMAP *zaza = NULL;
  ALLEGRO_BITMAP *coffe = NULL;
  ALLEGRO_AUDIO_STREAM *musica = NULL;
  ALLEGRO_SAMPLE *sample = NULL;
  //------------Variaveis de obstaculos----------
  int O_x = 384, O_y = 90, O_x1 = 64, O_y1 = 120, O_x2 = 128, O_y2 = 432,
      O_x3 = 192, O_y3 = 288, O_x4 = 256, O_y4 = 192, O_x5 = 320, O_y5 = 336,
      O_x6 = 400, O_y6 = 384, O_x7 = 448, O_y7 = 144, O_x8 = 512, O_y8 = 96,
      O_x9 = 576, O_y9 = 48, O_x10 = 490, O_y10 = 400;

  //----------------------Variaveis que movimentam os obstaculos ----
  float anda = 3;
  int returns[14];
  for (int position = 0; position < 14; position++){
    returns[position] = 1;
  }
  //------------Janela-------------------

  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_FONT *fonte = NULL;
  al_init();                                        // iniciar allegro
  display = al_create_display(LARGURA_T, ALTURA_T); // criação da janela
  al_install_keyboard();
  event_queue = al_create_event_queue();

  //------------------START ADDONS--------
  al_init_primitives_addon();
  al_init_font_addon();
  al_init_ttf_addon();
  al_init_image_addon();
  al_init_acodec_addon();
  al_install_audio();
  al_reserve_samples(0);

  //-----------------Fontes-----------
  fonte = al_load_font("font/action.ttf", 36, 0); // escolha da fonte

  //----------------Arquivos Externos----
  char url[] = "data/highscore.dat";
  FILE *arq;
  arq = fopen(url, "r+b");
  fscanf(arq, "%d", &highscore);

  //------------------Musica Principal----
  musica = al_load_audio_stream("audio/dbz8b.ogg", 4, 1024);
  al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
  al_set_audio_stream_playing(musica, true);

  //-------------------Fila de evento-----
  al_register_event_source(
      event_queue, al_get_keyboard_event_source()); // criar registro de todos
                                                    // os eventos - teclado
  al_register_event_source(event_queue,
                           al_get_display_event_source(
                               display)); // Criar registro de eventos- janela

  //---------------Cor inicial da tela----
  al_clear_to_color(al_map_rgb(0, 0, 0));

  //---------------------FUNDO----------------
  imagem = al_load_bitmap("img/preto.png");
  al_draw_bitmap(imagem, 0, 0, 0);
  //-----------------profes---------------------
  fefe = al_load_bitmap("img/fefee.png");
  zaza = al_load_bitmap("img/zaza.png");
  aster = al_load_bitmap("img/aster.png");
  coffe = al_load_bitmap("img/coffe.png");
  //----------------Mensagem inicial------

  al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARGURA_T / 2, 200,
                ALLEGRO_ALIGN_CENTRE, "Press Enter to play");
  al_flip_display();

  while (!exit) {
    while (!al_is_event_queue_empty(event_queue)) {
      ALLEGRO_EVENT evento;
      al_wait_for_event(event_queue, &evento);
      if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (evento.keyboard.keycode) {
        case ALLEGRO_KEY_ENTER:
          exit = true;
          break;
        }
      } else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        sair = fim = exit = true;
      }
    }
  }

  //----------------LOOP principal e movimentos-----
  while (!fim) {
    al_draw_bitmap(imagem, 0, 0, 0);
    al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARGURA_T / 2, 50,
                  ALLEGRO_ALIGN_CENTRE, "%d", flag);

    //------------------Troca de Cenário-----------------------
    if (flag == 3 && soum == 0) {
      soum++;
      al_rest(0.5);
    }
    if (flag == 6 && soum == 1) {
      soum++;
      al_rest(0.5);
    }

    //------------------Lógica----------------------
    ALLEGRO_EVENT ocorrencia;

    while (!al_is_event_queue_empty(event_queue)) {
      al_get_next_event(event_queue, &ocorrencia);

      if (ocorrencia.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (ocorrencia.keyboard.keycode) {
        case ALLEGRO_KEY_UP: // seta para cima
          if (y <= 1)
            y = ALTURA_T + 5;
          teclas[CIMA] = true;
          break;
        case ALLEGRO_KEY_DOWN: // seta para baixo
          if (y >= 480)
            y = -5;
          teclas[BAIXO] = true;
          break;
        case ALLEGRO_KEY_RIGHT: // seta para a direita
          if (x >= 640)
            x = -5;
          teclas[DIREITA] = true;
          break;
        case ALLEGRO_KEY_LEFT: // seta para a esquerda
          if (x <= 1)
            x = LARGURA_T + 5;
          teclas[ESQUERDA] = true;
          break;
        case ALLEGRO_KEY_F1:
          fefe = al_load_bitmap("img/fefee.png");
          coffe = al_load_bitmap("img/coffe.png");
          break;
        case ALLEGRO_KEY_F2:
          fefe = al_load_bitmap("img/monkey.png");
          coffe = al_load_bitmap("img/banana.png");
          break;
        case ALLEGRO_KEY_F3:
          fefe = al_load_bitmap("img/emilio.png");
          coffe = al_load_bitmap("img/bitcoin.png");
          break;
        }
      }
      if (ocorrencia.type == ALLEGRO_EVENT_KEY_UP) {
        switch (ocorrencia.keyboard.keycode) {
        case ALLEGRO_KEY_UP: // seta para cima
          teclas[CIMA] = false;
          break;
        case ALLEGRO_KEY_DOWN: // seta para baixo
          teclas[BAIXO] = false;
          break;
        case ALLEGRO_KEY_RIGHT: // seta para a direita
          teclas[DIREITA] = false;
          break;
        case ALLEGRO_KEY_LEFT: // seta para a esquerda
          teclas[ESQUERDA] = false;
          break;
        }
      }

      //-------------------- intensidade do movimento----
      y -= teclas[CIMA] * 7;
      y += teclas[BAIXO] * 7;
      x -= teclas[ESQUERDA] * 7;
      x += teclas[DIREITA] * 7;
    }

    //----------------------Fechar Janela--------------

    if (ocorrencia.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
      fim = true; // fecha a tela quando clicar no x
                  //----------------------Movimenta o obstaculo-----------
    if (O_y >= ALTURA_T || O_y <= 0)
      returns[0] *= -1;
    if (O_x1 >= LARGURA_T || O_x1 <= 0)
      returns[1] *= -1;
    if (O_y2 >= ALTURA_T || O_y2 <= 0)
      returns[2] *= -1;
    if (O_x3 >= LARGURA_T || O_x3 <= 0)
      returns[3] *= -1;
    if (O_x4 >= LARGURA_T || O_x4 <= 0)
      returns[4] *= -1;
    if (O_x5 >= LARGURA_T || O_x5 <= 0)
      returns[5] *= -1;
    if (O_y5 >= ALTURA_T || O_y5 <= 0)
      returns[6] *= -1;
    if (O_y6 >= ALTURA_T || O_y6 <= 0)
      returns[7] *= -1;
    if (O_y7 >= ALTURA_T || O_y7 <= 0)
      returns[8] *= -1;
    if (O_x7 >= LARGURA_T || O_x7 <= 0)
      returns[9] *= -1;
    if (O_y8 >= ALTURA_T || O_y8 <= 0)
      returns[10] *= -1;
    if (O_y9 >= ALTURA_T || O_y9 <= 0)
      returns[11] *= -1;
    if (O_x10 >= LARGURA_T || O_x10 <= 0)
      returns[12] *= -1;
    if (O_y10 >= ALTURA_T || O_y10 <= 0)
      returns[13] *= -1;

    //-------------------- Intensidade do movimento--------------
    O_y += anda * returns[0];
    O_x1 += anda * returns[1];
    O_y2 += anda * returns[2];
    O_x3 += anda * returns[3];
    O_x4 += anda * returns[4];
    O_x5 += anda * returns[5];
    O_y5 += anda * returns[6];
    O_y6 += anda * returns[7];
    O_y7 += anda * returns[8];
    O_x7 += anda * returns[9];
    O_y8 += anda * returns[10];
    O_y9 += anda * returns[11];
    O_x10 += anda * returns[12];
    O_y10 += anda * returns[13];

    //----------------------Quadrado personagem--------
    al_draw_bitmap(fefe, x, y, 0);

    //------------------------zaza----------------------
    if (flag % 3 == 0 && flag)
      al_draw_bitmap(zaza, zaza_x, zaza_y, 0);
    zaza_x = (zaza_x + 2) % LARGURA_T;
    zaza_y = (zaza_y + 2) % ALTURA_T;

    //-----------------------comida----------------------

    al_draw_bitmap(coffe, c_x - 2, c_y - 2, 0);

    //-----------------------obstaculos--------------------
    desenha(O_x, O_y);
    desenha(O_x1, O_y1);
    desenha(O_x2, O_y2);
    desenha(O_x3, O_y3);
    if (flag >= 3)
      desenha(O_x4, O_y4);
    if (flag >= 5)
      desenha(O_x5, O_y5);
    if (flag >= 8)
      desenha(O_x6, O_y6);
    if (flag >= 9)
      desenha(O_x7, O_y7);
    if (flag >= 10)
      desenha(O_x8, O_y8);
    if (flag >= 12)
      desenha(O_x9, O_y9);
    if (flag >= 15)
      desenha(O_x10, O_y10);

    //----------------------Atualizar movimento--------
    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));

    //---------------------testes de colisão-----------

    if (colide(c_x, c_y)) {
      flag++;
      anda += 0.05;
      c_x = (rand()) % (LARGURA_T);
      c_y = (rand()) % (ALTURA_T);
    }

    if (colide(O_x, O_y) || colide(O_x1, O_y1) || colide(O_x2, O_y2) ||
        colide(O_x3, O_y3) || (colide(O_x4, O_y4) && flag >= 3) ||
        (colide(O_x5, O_y5) && flag >= 5) ||
        (colide(O_x6, O_y6) && flag >= 8) ||
        (colide(O_x7, O_y7) && flag >= 9) ||
        (colide(O_x8, O_y8) && flag >= 10) ||
        (colide(O_x9, O_y9) && flag >= 12) ||
        (colide(O_x10, O_y10) && flag >= 15)) {

      //---------------Musica quando morre-----------

      al_destroy_audio_stream(musica);
      musica = al_load_audio_stream("audio/erro.ogg", 10, 1024);
      al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
      al_set_audio_stream_playing(musica, true);
      al_rest(2);

      //-------------Queda quando morre---------------
      for (i = 0; i < 25; i++) {
        y -= 5;
        al_draw_bitmap(fefe, x, y, 0);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
      }

      for (i = 0; i < 25; i++) {
        y += 30;
        al_draw_bitmap(fefe, x, y, 0);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
      }

      fim = true;
    }

    //----------------------fim do loop Principal----------------
  }

  //------------------Verificação do High Score-------
  if (flag > highscore) {
    fclose(arq);
    system("rm data/highscore.dat");
    system("touch data/highscore.dat");
    char url[] = "data/highscore.dat";
    FILE *arq;
    arq = fopen(url, "w+");
    fprintf(arq, "%d\n", flag);
    highscore = flag;
  }

  //--------------------------Retorno para menu principal ou fim--------
  al_draw_bitmap(imagem, 0, 0, 0);
  al_draw_textf(fonte, al_map_rgb(255, 255, 0), LARGURA_T / 2, 100,
                ALLEGRO_ALIGN_CENTRE, "Score: %d", flag);
  al_draw_textf(fonte, al_map_rgb(255, 255, 0), LARGURA_T / 2, 300,
                ALLEGRO_ALIGN_CENTRE, "High Score: %d", highscore);
  al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARGURA_T / 2, 200,
                ALLEGRO_ALIGN_CENTRE, "Press Enter to continue");
  al_flip_display();
  fclose(arq);
  while (!sair) {
    while (!al_is_event_queue_empty(event_queue)) {
      ALLEGRO_EVENT evento;
      al_wait_for_event(event_queue, &evento);
      if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (evento.keyboard.keycode) {
        case ALLEGRO_KEY_ENTER:
          al_destroy_display(display); // fecha a janela
          al_destroy_event_queue(event_queue);
          al_destroy_audio_stream(musica);
          al_destroy_sample(sample);
          system("./bin/game");
          break;
        }
      } else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        sair = true;
    }
  }

  //------------------Fim Efetivo----------------
  al_destroy_audio_stream(musica);
  al_destroy_sample(sample);
  al_destroy_display(display);         // fecha a janela
  al_destroy_event_queue(event_queue); // zera a fila de eventos
}
