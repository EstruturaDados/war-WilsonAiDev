# 🗺️ Desafio WAR - Conquista de Territórios

![C](https://img.shields.io/badge/Language-C-blue.svg)
![Status](https://img.shields.io/badge/Status-Em%20Desenvolvimento-yellow.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Estácio](https://img.shields.io/badge/Universidade-Estácio%20de%20Sá-red.svg)

## 📚 Sobre o Projeto

Este projeto é parte do desafio proposto na disciplina de **Estrutura de Dados** do curso de **Engenharia de Software** da **Universidade Estácio de Sá**. O desafio consiste em desenvolver diferentes versões do jogo de estratégia **WAR**, aplicando conceitos fundamentais da linguagem C e estruturas de dados.

O projeto foi estruturado em três níveis progressivos de dificuldade (**Novato**, **Aventureiro** e **Mestre**), permitindo uma evolução gradual no aprendizado de programação em C, desde conceitos básicos até técnicas avançadas de modularização e gerenciamento de memória.

---

## 🎯 Objetivo

O objetivo principal é implementar um sistema de gerenciamento de territórios inspirado no jogo WAR, onde:
- No **Nível Novato**, aprende-se a trabalhar com estruturas de dados básicas
- No **Nível Aventureiro**, evolui-se para alocação dinâmica de memória e simulação de batalhas
- No **Nível Mestre**, aplica-se modularização completa e sistema de missões

Cada implementação foca em aspectos específicos da programação, permitindo consolidar conhecimentos teóricos através de uma aplicação prática e envolvente.

---

## 📁 Estrutura do Projeto

Este repositório contém implementações separadas para cada nível do desafio:

```
war-WilsonAiDev/
├── war-novato.c       # Nível 1: Cadastro de territórios (vetor estático)
├── war-aventureiro.c  # Nível 2: Batalhas estratégicas (alocação dinâmica)
├── war-mestre.c       # Nível 3: Sistema de missões (modularização total)
├── war.c              # Template base para desenvolvimento
└── README.md
```

### 🔧 Como Compilar e Executar

```bash
# Nível Novato
gcc war-novato.c -o war-novato
./war-novato

# Nível Aventureiro
gcc war-aventureiro.c -o war-aventureiro
./war-aventureiro

# Nível Mestre
gcc war-mestre.c -o war-mestre
./war-mestre
```

---

## 🧩 Níveis do Desafio

### 🟢 Nível Novato: Cadastro Inicial dos Territórios

**Objetivo:** Criar uma base sólida com estruturas de dados e entrada/saída.

**Funcionalidades:**
- Definição de `struct Territorio` com nome, cor do exército e número de tropas
- Vetor estático de 5 elementos para armazenar territórios
- Interface de cadastro via terminal
- Exibição formatada do mapa de territórios

**Conceitos Abordados:**
- `struct` (estruturas)
- Arrays estáticos
- Entrada/saída com `scanf`, `fgets` e `printf`
- Manipulação de strings

---

### 🔵 Nível Aventureiro: Batalhas Estratégicas

**Objetivo:** Implementar lógica de jogo com gerenciamento dinâmico de memória.

**Funcionalidades:**
- Substituição do vetor estático por alocação dinâmica com `calloc`
- Sistema de combate entre territórios
- Simulação de dados de ataque e defesa com números aleatórios
- Conquista de territórios baseada em batalhas

**Conceitos Abordados:**
- Ponteiros e referências
- Alocação dinâmica de memória (`calloc`, `free`)
- Geração de números aleatórios (`rand()`, `srand()`)
- Funções e modularização básica
- Lógica condicional complexa

---

### 🟣 Nível Mestre: Missões e Modularização Total

**Objetivo:** Aplicar boas práticas de engenharia de software com código limpo e modular.

**Funcionalidades:**
- Sistema completo de missões com objetivos variados
- Menu interativo com múltiplas opções
- Verificação automática de condições de vitória
- Inicialização automática de territórios
- Arquitetura completamente modularizada

**Conceitos Abordados:**
- Modularização e separação de responsabilidades
- `const` correctness (passagem por referência constante)
- Design de funções especializadas
- Game loop e estado do jogo
- Passagem por valor vs. passagem por referência

---

## 📖 Conceitos de Programação Consolidados

Ao completar este desafio, os seguintes conceitos são praticados e consolidados:

### Fundamentos
- ✅ Estruturas de dados (`struct`)
- ✅ Arrays e vetores (estáticos e dinâmicos)
- ✅ Entrada e saída formatada
- ✅ Manipulação de strings

### Intermediário
- ✅ Ponteiros e endereços de memória
- ✅ Alocação e liberação dinâmica de memória
- ✅ Funções e modularização
- ✅ Números aleatórios
- ✅ Lógica de controle de fluxo

### Avançado
- ✅ Arquitetura de software modular
- ✅ Const correctness
- ✅ Gerenciamento de estado de aplicação
- ✅ Design patterns básicos (game loop)
- ✅ Boas práticas de programação em C

---

## 🎓 Informações Acadêmicas

- **Instituição:** Universidade Estácio de Sá
- **Curso:** Engenharia de Software
- **Disciplina:** Estrutura de Dados
- **Desenvolvedor:** Wilson Oliveira

---

## 📝 Licença

Este projeto está sob a licença MIT. Sinta-se livre para usar, modificar e distribuir conforme necessário.

---

## 🚀 Próximos Passos

- [x] Implementar Nível Novato
- [x] Implementar Nível Aventureiro
- [x] Implementar Nível Mestre
- [ ] Adicionar testes unitários
- [ ] Documentar código com comentários detalhados

---

⭐ **Desenvolvido como parte do aprendizado em Estrutura de Dados - Estácio de Sá**
