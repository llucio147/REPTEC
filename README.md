# REPTEC

Este projeto apresenta o desenvolvimento de um aquaterrário automatizado, idealizado inicialmente como Trabalho de Conclusão de Curso (TCC). A proposta mostrou-se viável desde os primeiros testes, o que motivou a criação de uma placa de circuito personalizada. A princípio, utilizou-se uma placa Arduino para a programação e compilação do código, bem como para a integração com sensores compatíveis. Após comprovar a eficiência do sistema, desenvolveu-se uma placa própria, eliminando a necessidade do Arduino. Os desenhos e esquemas do circuito encontram-se disponíveis no repositório correspondente.

Tanto o código quanto a placa estão protegidos contra plágio, com pedido de patente registrado junto ao Instituto Nacional da Propriedade Industrial (INPI), sob número de protocolo 870250028442 e número de pedido de patente BR 20 2025 006992 5.

O projeto foi desenvolvido em linguagem Arduino (.ino), com codificação em C++. Tem como principal funcionalidade a criação de um ambiente controlado por meio de sensores, atuadores e controladores. Variáveis como temperatura, umidade e nível de água podem ser ajustadas conforme a necessidade, permitindo adaptar o sistema para diferentes aplicações, como aquaterrários ou outros ambientes que demandem controle climático e hídrico.

O sistema realiza o controle da temperatura interna, comparando-a com a externa. Caso a temperatura interna esteja abaixo de 28 °C, o sistema aciona o aquecedor; se estiver acima de 32 °C, o aquecedor é desligado automaticamente. A cada 1500 milissegundos, os sensores realizam novas leituras das variáveis ambientais.

O controle da radiação ultravioleta (UV) é configurado para ser ativado diariamente, em horário programado via RTC (Real-Time Clock), com duração pré-definida — atualmente, de uma hora por dia —, atuando como agente antibacteriano e auxiliar no controle biológico da água.

A troca de água também é realizada de forma automática, sem necessidade de intervenção humana. No dia e horário programados, o sistema verifica o nível de água por meio de dois sensores que identificam os estados de "vazio", "médio" e "cheio". Quando o nível máximo é detectado, a bomba de escoamento é acionada. Ao atingir o estado de "vazio", a bomba é desligada automaticamente para evitar danos por funcionamento a seco. Em seguida, uma válvula solenoide é acionada para iniciar o reabastecimento do ambiente. O enchimento é interrompido automaticamente quando os sensores indicam que o nível ideal foi atingido, prevenindo inundações.

Todas as informações de status — como data e hora, nível de água, temperaturas interna e externa, ativação do aquecimento e da radiação UV — são exibidas de forma intuitiva em um módulo LCD. Todo o controle é realizado pela placa eletrônica desenvolvida especificamente para este projeto.
