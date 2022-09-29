// Assinaturas View
void viewMenu();
void viewMenuJogadores();
void imprimirMsg(int);
void mostrarMsgJogador(int);
void mostrarMsgPeca(int, int);
void viewJogador();
void imprimirMesa();
void viewMenuFimDaPartida();

// Assinaturas Model
void gerarPecas();
void embaralharPecas();
void mudaLado(int);
void distribuirPecas();

// Assinaturas Controller
void menuDomino();
int maiorPeca();
void iniciarJogo();
void menuJogador();
void compraPeca();
int jogarPeca();
int verificaJogada(int, int);
int verificaFim();
int jogoTrancado();
int somaPJogador();
int verificaRobo();
void trocarTurno();

// Assinaturas Controller - Manipulação de arquivos
void salvarJogo();
void recuperarJogo();
