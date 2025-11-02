# 🚗 VrumVrum - Sistema de Gestão de Veículos

Sistema em C para gerenciamento completo de compra e venda de veículos, desenvolvido para facilitar o controle de estoque, histórico de transações e relatórios financeiros de uma revenda de automóveis.

## 📋 Funcionalidades

### 1. 🛒 Compra de Veículos
- Pesquisa e aquisição de veículos do arquivo de ofertas
- Aplicação automática de taxas por marca
- Transferência automática para o estoque

### 2. 💰 Venda de Veículos
- Sistema de busca e filtragem de veículos em estoque
- Registro de informações do cliente
- Gravação automática de data e hora da transação
- Geração de histórico de vendas

### 3. ✏️ Alteração de Dados
- Cadastro de novas marcas com taxas personalizadas
- Modificação de dados de veículos no estoque
- Atualização de informações de marcas cadastradas

### 4. 🔍 Consulta ao Catálogo
- Visualização de veículos em estoque
- Consulta de ofertas disponíveis
- Sistema de filtros personalizados

### 5. 📊 Relatórios
- Relatório de histórico de compras
- Relatório de histórico de vendas
- Filtros por período (data inicial e final)
- Opção de exibição em tela ou arquivo

### 6. 💾 Backup
- Criação de backups de todos os arquivos do sistema
- Exclusão de backups antigos
- Armazenamento seguro em formato binário

## 🗂️ Estrutura de Arquivos

O sistema utiliza arquivos CSV para persistência de dados:

- `veiculos_ofertas.csv` - Veículos disponíveis para compra
- `veiculos_estoque.csv` - Estoque atual da revenda
- `historico_vendas.csv` - Registro completo de vendas
- `historico_compras.csv` - Registro completo de compras
- `Marcas.csv` - Cadastro de marcas e suas respectivas taxas
- `Backup/` - Diretório com backups em formato binário

## 🛠️ Compilação e Execução

```bash
# Compilar o projeto
make

# Executar o sistema
./main
```

## 💡 Características Técnicas

- Desenvolvido em C puro
- Interface de console interativa
- Manipulação de arquivos CSV
- Sistema de ordenação (por preço e marca)
- Gestão automática de datas e horários
- Locale configurado para Português

## 📝 Licença

Este projeto foi desenvolvido para fins educacionais.
