READ_LONG  0x64 "abil_off" ELSE 0
READ_SHORT 0x68 "abil_num" ELSE 0
READ_LONG  0x6a "fx_off" ELSE 0
READ_SHORT 0x6e "fx_idx" ELSE 0
READ_SHORT 0x70 "fx_num" ELSE 0

PATCH_IF (abil_off > 0x71) AND (fx_off > 0x71) BEGIN
  FOR (index = fx_idx ; index < fx_num ; index = index + 1) BEGIN
    READ_SHORT ("%fx_off%" +        ("%index%" * 0x30)) "opcode"
    READ_BYTE  ("%fx_off%" + 0x02 + ("%index%" * 0x30)) "target"
    READ_BYTE  ("%fx_off%" + 0x03 + ("%index%" * 0x30)) "power"
    READ_LONG  ("%fx_off%" + 0x04 + ("%index%" * 0x30)) "param1"
    READ_LONG  ("%fx_off%" + 0x08 + ("%index%" * 0x30)) "param2"
    READ_BYTE  ("%fx_off%" + 0x0c + ("%index%" * 0x30)) "timing"
    READ_BYTE  ("%fx_off%" + 0x0d + ("%index%" * 0x30)) "dispel"
    READ_LONG  ("%fx_off%" + 0x0e + ("%index%" * 0x30)) "duration"
    READ_BYTE  ("%fx_off%" + 0x12 + ("%index%" * 0x30)) "prob1"
    READ_BYTE  ("%fx_off%" + 0x13 + ("%index%" * 0x30)) "prob2"
    READ_ASCII ("%fx_off%" + 0x14 + ("%index%" * 0x30)) "resref"
    READ_LONG  ("%fx_off%" + 0x1c + ("%index%" * 0x30)) "diccnt"
    READ_LONG  ("%fx_off%" + 0x20 + ("%index%" * 0x30)) "dicsid"
    READ_LONG  ("%fx_off%" + 0x24 + ("%index%" * 0x30)) "savtyp"
    READ_LONG  ("%fx_off%" + 0x28 + ("%index%" * 0x30)) "savbon"
    FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN
      PATCH_IF ("%index1%" != "%index%") BEGIN
        READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
        READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
        READ_BYTE  ("%fx_off%" + 0x03 + ("%index1%" * 0x30)) "eff_power"
        READ_LONG  ("%fx_off%" + 0x04 + ("%index1%" * 0x30)) "eff_param1"
        READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
        READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
        READ_BYTE  ("%fx_off%" + 0x0d + ("%index1%" * 0x30)) "eff_dispel"
        READ_LONG  ("%fx_off%" + 0x0e + ("%index1%" * 0x30)) "eff_duration"
        READ_BYTE  ("%fx_off%" + 0x12 + ("%index1%" * 0x30)) "eff_prob1"
        READ_BYTE  ("%fx_off%" + 0x13 + ("%index1%" * 0x30)) "eff_prob2"
        READ_ASCII ("%fx_off%" + 0x14 + ("%index1%" * 0x30)) "eff_resref"
        READ_LONG  ("%fx_off%" + 0x1c + ("%index1%" * 0x30)) "eff_diccnt"
        READ_LONG  ("%fx_off%" + 0x20 + ("%index1%" * 0x30)) "eff_dicsid"
        READ_LONG  ("%fx_off%" + 0x24 + ("%index1%" * 0x30)) "eff_savtyp"
        READ_LONG  ("%fx_off%" + 0x28 + ("%index1%" * 0x30)) "eff_savbon"
        PATCH_IF ("%opcode%" = "%eff_opcode%") AND
                  ("%target%" = "%eff_target%") AND
                  ("%power%" = "%eff_power%") AND
                  ("%param1%" = "%eff_param1%") AND
                  ("%param2%" = "%eff_param2%") AND
                  ("%timing%" = "%eff_timing%") AND
                  ("%dispel%" = "%eff_dispel%") AND
                  ("%duration%" = "%eff_duration%") AND
                  ("%prob1%" = "%eff_prob1%") AND
                  ("%prob2%" = "%eff_prob2%") AND
                  ("%resref%" STR_EQ "%eff_resref%") AND
                  ("%diccnt%" = "%eff_diccnt%") AND
                  ("%dicsid%" = "%eff_dicsid%") AND
                  ("%savtyp%" = "%eff_savtyp%") AND
                  ("%savbon%" = "%eff_savbon%") BEGIN
          PATCH_PRINT "HI62: %SOURCE_FILE% - Effect #%index1% (Opcode %opcode%) matches Effect #%index%! Removing..."
          offset = "%fx_off%" + ("%index1%" * 0x30)
          value  = 0x30
          DELETE_BYTES offset value
          SOURCE_SIZE = SOURCE_SIZE - value
          PATCH_IF ("%abil_off%" > "%fx_off%") BEGIN
            SET "abil_off" = "abil_off" - 0x30
            WRITE_LONG 0x64 %abil_off%
          END
          FOR (index2 = 0 ; index2 < abil_num ; index2 = index2 + 1) BEGIN
            READ_SHORT  ("%abil_off%" + 0x20 + ("%index2%" * 0x38)) "abil_fx_idx"
            PATCH_IF ("%abil_fx_idx%" > "%index1%") BEGIN
              SET "abil_fx_idx" = "abil_fx_idx" - 1
              WRITE_SHORT ("%abil_off%" + 0x20 + ("%index2%" * 0x38)) "abil_fx_idx"
            END
          END
          SET "index1" = 0 - 1
          SET "fx_num" = "fx_num" - 1
          WRITE_SHORT 0x70 %fx_num%
        END
      END
    END
  END
END
