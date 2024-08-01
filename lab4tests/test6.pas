PROGRAM test6 ;
    VAR
        aaa, bbb : integer;

    PROCEDURE proc1 ;
    VAR
        aaa, bbb : integer;

        PROCEDURE proc1a ( VAR aaa : integer ; bbb : integer );
        BEGIN
            WRITE(aaa, bbb);
        END;

    BEGIN
       proc1a(aaa, bbb);
    END;

BEGIN
   proc1;
   WRITE(aaa, bbb);
END.

