-- Cosas para que el sistema funcione
INSERT INTO clientes (nombreCompleto, numeroTelefono)
VALUES ('Mostrador', '0000000000');
INSERT INTO empresa (nombre, direccion, telefono, mensajePersonal)
VALUES ("", "", "", "");
INSERT INTO comun (clave, valor)
VALUES ('NOMBRE_IMPRESORA', '');
INSERT INTO comun (clave, valor)
VALUES ('CREATED_BY', 'parzibyte');
INSERT INTO comun (clave, valor)
VALUES ('MODO_IMPRESION_CODIGOS', 'codigo');
INSERT INTO comun (clave, valor)
VALUES ('MODO_LECTURA_CODIGOS', 'codigo');
INSERT INTO comun (clave, valor)
VALUES ('NUMERO_COPIAS_TICKET_CONTADO', 1);
INSERT INTO comun (clave, valor)
VALUES ('NUMERO_COPIAS_TICKET_APARTADO', 1);
INSERT INTO comun (clave, valor)
VALUES ('NUMERO_COPIAS_TICKET_ABONO', 1);
-- Los permisos que todos los usuarios pueden tener
INSERT INTO permisos (clave, descripcion)
VALUES ('RegistrarVentaContado', 'Hacer ventas al contado e imprimir tickets de las mismas'),
       ('RegistrarApartado', 'Hacer apartados y realizar abonos a dichos apartados. También imprimir tickets o
comprobantes de ambos.'),
       ('VerReporteCaja', 'Ver e imprimir el reporte de caja general o por usuario'),
       ('VerUsuarios',
        'Ver los usuarios existentes. Necesario para filtrar reportes por usuarios (si lo concede, no supone ningún riesgo)'),
       ('RegistrarUsuario', 'Agregar un nuevo usuario al sistema, pero no por ello asignarle permisos'),
       ('VerAjustes',
        'Ver los ajustes, como lo son los datos de la empresa, nombre de la impresora, modo de lectura de códigos, entre otros. Necesario para vender.'),
       ('CambiarAjustes', 'Cambiar ajustes como los datos de la empresa, nombre de la impresora, entre otros'),
       ('VerGraficas', 'Ver gráficas de ventas por mes o año, así como estadísticas de productos'),
       ('RegistrarIngreso', 'Registrar un ingreso o entrada de efectivo'),
       ('RegistrarEgreso', 'Registrar egreso o salida de efectivo'),
       ('VerVentasContado', 'Ver el reporte de ventas al contado'),
       ('CambiarFechaVencimientoApartado', 'Cambiar la fecha de vencimiento de un apartado'),
       ('VerApartados', 'Ver el reporte de apartados, así como de los abonos que se han hecho a los mismos'),
       ('CambiarProductoDeApartado', 'Cambiar un producto de un apartado por otro de igual o mayor precio'),
       ('VerClientes', 'Ver los clientes, así como su historial de compras al contado y apartados'),
       ('AutocompletarClientes', 'Autocompletado de clientes (necesario para hacer ventas o apartados)'),
       ('RegistrarCliente',
        'Registrar un nuevo cliente, ya sea desde el momento de vender o desde Clientes. Necesario para registrar cliente al vender'),
       ('ActualizarCliente', 'Modificar los datos de un cliente'),
       ('EliminarCliente', 'Eliminar un cliente y todo su historial'),
       ('VerReporteDeInventario', 'Ver el reporte general del inventario'),
       ('VerProductos', 'Ver los detalles de todos los productos existentes, así como exportarlos a CSV o Excel'),
       ('AutocompletarProductos',
        'Autocompletado de productos (necesario para cambiar producto de apartado o para buscar un producto por su descripción al vender)'),
       ('RegistrarProducto', 'Registrar un producto e importar archivos'),
       ('ActualizarProducto',
        'Modificar o editar un producto, por ejemplo aumentar o disminuir la existencia, cambiar el código de barras, precios, entre otros.'),
       ('ModificarYVerPermisos',
        'Asignar, agregar o modificar permisos de cualquier usuario, incluso del administrador. Se recomienda tener cuidado con esta opción'),
       ('EliminarProducto', 'Eliminar un producto'),
       ('VerProductoPorCodigoONumero',
        'Ver un producto por código de barras o número. Necesario para realizar ventas al contado y apartados.');
