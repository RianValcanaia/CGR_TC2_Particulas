<div align="center" id="topo">

<img src="https://media.giphy.com/media/iIqmM5tTjmpOB9mpbn/giphy.gif" width="200px" alt="Gif animado"/>

# <code><strong> Modelagem 3D com quádricas em OpenGL</strong></code>

<em>Implementação de um sistema de partículas para simulação física de fluidos na disciplina de Computação Gráfica.</em>

[![C Usage](https://img.shields.io/badge/C-100%25-blue?style=for-the-badge&logo=c)]()
[![Status](https://img.shields.io/badge/Status-Concluído-green?style=for-the-badge)]()
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Visite%20meu%20perfil-blue?style=for-the-badge&logo=linkedin)](https://www.linkedin.com/in/rian-carlos-valcanaia-b2b487168/)

</div>

## Índice

- [📌 Objetivos](#-objetivos)
- [📥 Entradas do sistema](#-entradas-do-sistema)
- [🧱 Estruturas de Dados](#-estruturas-de-dados)
- [🧰 Funcionalidade](#-funcionalidade)
- [📂 Como executar](#-como-executar)
- [👨‍🏫 Envolvidos](#-envolvidos)
- [📅 Curso](#-curso)
- [📄 Código-fonte](#-código-fonte)

## 📌 Objetivos
O trabalho tem como objetivo a criação de uma simulação visual baseada em física utilizando a técnica de Sistemas de Partículas em OpenGL.
* Implementar uma estrutura de dados eficiente para gerenciar milhares de partículas simultâneas.
* Simular leis físicas básicas, como velocidade inicial, angulação e aceleração da gravidade.
* Gerenciar o ciclo de vida das partículas (nascimento, atualização, morte e renascimento).
* Aplicar efeitos visuais de transparência (Alpha Blending) para simular o desvanecimento da água.

  
[⬆ Voltar ao topo](#topo)

## 🧱 Estruturas de Dados
A simulação é baseada em um vetor estático de estruturas, permitindo acesso rápido e reciclagem de memória.
### 🔸 s_particulas

Estrutura que define as propriedades físicas e visuais de uma única partícula.
```c
struct s_particulas {
    float x, y;           // Posição atual
    float veloc_x, veloc_y; // Vetor velocidade
    float r, g, b, a;     // Cor (RGB) e Transparência (Alpha)
    unsigned tempo_vida;  // Contador de frames restantes
    unsigned tempo_vida_inicial; // Referência para cálculo do fade-out
} particulas[NUM_PARTICULAS];
```
### 🔸 Definições Globais

Constantes que controlam o comportamento da simulação:
```c
NUM_PARTICULAS: 5000 (Total de partículas no sistema).
GRAVIDADE: 0.0008 (Força g aplicada no eixo Y a cada frame).
PARTICULAS_POR_FRAME: 10 (Taxa de emissão do chafariz).
```

[⬆ Voltar ao topo](#topo)

## 🧰 Funcionalidade

### 🔹 Motor Físico (Physics Engine)

A cada quadro renderizado, o sistema atualiza a posição de todas as partículas vivas baseando-se em cinemática básica:
* Gravidade: A velocidade vertical é decrementada pela constante gravitacional.
* Deslocamento: A posição é atualizada somando-se a velocidade atual.

### 🔹 Gerenciamento de Ciclo de Vida

* Nascimento (reseta_Particulas): Inicializa uma partícula com velocidade aleatória e ângulo entre -45° e 45° usando trigonometria.
* Morte e Renascimento: Quando o tempo_vida chega a zero, a partícula é marcada como morta e reintroduzida na fila para ser "emitida" novamente na origem do chafariz.

### 🔹 Renderização e Efeitos

* Primitivas: Utiliza GL_POINTS para desenhar as partículas.
* Transparência: Habilita GL_BLEND para criar o efeito visual de água desaparecendo conforme a partícula "morre" (fade-out), calculado pela razão entre a vida atual e a vida inicial.

[⬆ Voltar ao topo](#topo)

## 📂 Como executar

Para compilar e executar, é necessário ter as bibliotecas OpenGL, GLU e GLUT instaladas. Como o código utiliza funções matemáticas (sin, cos), é essencial linkar a biblioteca matemática (-lm).

Execute o seguinte comando no terminal:

```bash
gcc chafariz.c -lglut -lGL -lGLU -lm -o chafariz && ./chafariz
```

[⬆ Voltar ao topo](#topo)

## 👨‍🏫 Envolvidos
* **Professor**: André Tavares da Silva
* **Estudantes**:
  * [Rian Valcanaia](https://github.com/RianValcanaia)
  * Lucas Oliveira Macedo

[⬆ Voltar ao topo](#topo)

## 📅 Curso

* **Universidade**: Universidade do Estado de Santa Catarina (UDESC)
* **Disciplina**: Computação Gráfica
* **Semestre**: 5º

[⬆ Voltar ao topo](#topo)

## 📄 Código-fonte

🔗 [https://github.com/RianValcanaia/TC2_Particulas](https://github.com/RianValcanaia/TC2_Particulas)

[⬆ Voltar ao topo](#topo)
