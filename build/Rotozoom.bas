DEFINT A-Z
SCREEN 13
CONST PI = 3.1415926#

FOR c = 0 TO 255
    PALETTE c, (c \ 4) * (1 + 256 + 65536)
NEXT
COLOR 255

DIM SHARED tile(15, 15) AS INTEGER
FOR x = 0 TO 15
    FOR y = 0 TO 15
        tile(y, x) = (y AND x) * 16
    NEXT
NEXT x

DIM divs(3840) AS INTEGER
FOR d = 0 TO 3840
    divs(d) = d \ 256
NEXT d

DIM sins(128) AS INTEGER
DIM coss(128) AS INTEGER
FOR s = 0 TO 128
    sins(s) = 256 * SIN(s * PI / 64) * (COS(s * PI / 64) + 1.5)
    coss(s) = 256 * COS(s * PI / 64) * (COS(s * PI / 64) + 1.5)
NEXT s

DIM SHARED m100(-512 - 256 TO 512 + 256) AS INTEGER
FOR m = -512 - 256 TO 512 + 256
    m100(m) = m * 100
NEXT
DIM SHARED m160(-512 - 256 TO 512 + 256) AS INTEGER
FOR m = -512 - 256 TO 512 + 256
    m160(m) = m * 160
NEXT

'DIM z(128) AS SINGLE
'FOR s = 0 TO 128
'    z(s) = COS(s * PI / 64) + 1.5
'NEXT s

t# = TIMER
DEF SEG = &HA000
DO
    angle = (angle + 1) AND 127
    f = f + 1
    ca = coss(angle)
    sa = sins(angle)
    yca = 25600 - m100(coss(angle)) + m160(sins(angle))
    ysa = 40960 - m100(sins(angle)) - m160(coss(angle))
    p = 0
    FOR y = 0 TO 199
        xrot = ysa
        yrot = yca
        FOR x = 0 TO 319
            col = tile(divs(xrot AND 3840), divs(yrot AND 3840))
            POKE p, col
            p = p + 1
            xrot = xrot + ca
            yrot = yrot - sa
        NEXT x
        yca = yca + ca
        ysa = ysa + sa
    NEXT y
LOOP UNTIL INKEY$ <> ""
PRINT f / (TIMER - t#)
DO
LOOP WHILE INKEY$ = ""

