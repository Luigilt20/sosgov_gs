#participantes: 
Luigi Thiengo pires - RM 560755
Felipe Gomes Molinari Lopes - RM 559885

# Sistema Inteligente de Monitoramento e Alerta de Enchentes

## Problema Identificado

Enchentes urbanas afetam significativamente áreas residenciais e comerciais, causando prejuízos materiais, riscos à vida humana e problemas na mobilidade urbana. A ausência de monitoramento em tempo real e de sistemas automatizados de alerta compromete a resposta rápida das autoridades e da população.

## Solução Proposta

Este projeto apresenta um sistema de **detecção precoce e alerta de enchentes** baseado em tecnologias de **Edge Computing e IoT**. Sensores de nível de água e umidade realizam a coleta de dados ambientais em tempo real, enviando essas informações para um dashboard online que possibilita o acompanhamento contínuo e a emissão de alertas automáticos em situações de risco.

## Objetivos

- Monitorar o nível de água e a umidade do ar em tempo real.
- Detectar automaticamente situações de risco.
- Emitir alertas para tomada de decisão rápida.
- Fornecer dados acessíveis para cidadãos e autoridades.

## Arquitetura da Solução

### Camada IoT (Sensores e Microcontrolador)

- **ESP32 DevKit V4**: microcontrolador principal para leitura dos sensores e envio dos dados.
- **DHT22**: sensor digital de temperatura e umidade.
- **HC-SR04**: sensor ultrassônico utilizado para medir o nível de água.
- **Wokwi**: plataforma utilizada para simulação completa do circuito e código.

### Camada de Comunicação (Back-End)

- **HTTPS**: protocolo utilizado para envio seguro dos dados.
- Integração com a plataforma **TagoIO** para recebimento e roteamento da informação.
- Os dados são transmitidos em tempo real da borda para a nuvem.

### Camada de Aplicação (Dashboard e Alertas)

- **TagoIO Dashboard** para visualização gráfica em tempo real dos dados.
- Geração de alertas automáticos quando o nível da água ou a umidade ultrapassam limites críticos.
- Interface acessível, permitindo uso por equipes técnicas ou gestores públicos.

## Tecnologias Utilizadas

| Componente         | Descrição                                      |
|--------------------|-----------------------------------------------|
| ESP32              | Microcontrolador principal                    |
| DHT22              | Sensor de umidade                             |
| HC-SR04            | Sensor de nível de água                       |
| Arduino Framework  | Lógica de controle e leitura de sensores      |
| TagoIO             | Plataforma de IoT para dashboard e alertas    |
| HTTPS              | Protocolo de envio seguro dos dados           |
| Wokwi              | Simulador virtual de circuito IoT             |

## Funcionamento do Sistema

- O ESP32 coleta os dados dos sensores em intervalos regulares.
- Os dados são enviados via HTTPS para a nuvem (TagoIO).
- Um dashboard exibe os valores em tempo real e armazena o histórico.
- Quando os valores excedem os limites definidos (ex: nível de água > 1500 mm, umidade > 60%), alertas são automaticamente gerados.

## Como Simular

### Executar no Wokwi

- Acesse o projeto pelo link: [https://wokwi.com/projects/432500862184098817](https://wokwi.com/projects/432500862184098817)
- O código está configurado para simular a coleta de dados e envio via HTTPS.
- Visualize os dados via terminal serial ou integre com seu ambiente TagoIO.

### Acesso ao Dashboard TagoIO

- Link do dashboard: [https://683caaab1fed38000abfad4a.us-e1.tago.run/dashboards/info/683cab714c2704000962ca65](https://683caaab1fed38000abfad4a.us-e1.tago.run/dashboards/info/683cab714c2704000962ca65)
- Plataforma: [https://admin.tago.io](https://admin.tago.io)  
- E-mail: `sosgov@access.com`  
- Senha: `access`  
