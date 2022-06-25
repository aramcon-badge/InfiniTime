#pragma once
#include <nrf_log.h>

namespace CTF
{

    const uint32_t FLAGS[][3] = {
        {1993, 6, 9}, // first DEFCON
        {2022, 6, 15}, // TEST TODO REMOVE
        {1996, 11, 8}, // Smashing The Stack For Fun And Profit
        {2020, 6, 11}, // TEST TODO REMOVE
        {2020, 6, 11}, // TEST TODO REMOVE
    };

    static const uint32_t NUM_OF_CTF_LVLS = 5;
    static char solved[NUM_OF_CTF_LVLS] = {'.','.','.','.','.'};

    static void get_solved(char* out_arr)
    {
        memcpy(out_arr, solved, sizeof(out_arr));
    }

    static bool ctf_input(int year, int month, int day)
    {
        NRF_LOG_INFO("check flag %04d-%02d-%02d", year, month, day);

        static const uint32_t INVALID_FLAG_INDEX = -1;
        uint32_t valid_flag_index = INVALID_FLAG_INDEX; 
        for (uint32_t i=0; i< sizeof(FLAGS)/sizeof(FLAGS[0]); i++)
        {
            if (FLAGS[i][0] == year && 
                FLAGS[i][1] == month && 
                FLAGS[i][2] == day)
                {
                    valid_flag_index = i;
                    NRF_LOG_INFO("valid flag: %d", valid_flag_index);
                    break;
                }
        }

        if (valid_flag_index != INVALID_FLAG_INDEX)
        {
            solved[valid_flag_index] = 'F';
            memset((void*)solved, 47, sizeof(solved));
            NRF_LOG_INFO("valid flag flipped");
            //return true;
        }

          NRF_LOG_INFO("flags in CTF:  %c%c%c%c%c", 
                          CTF::solved[0],
                          CTF::solved[1],
                          CTF::solved[2],
                          CTF::solved[3],
                          CTF::solved[4]);
    }

    //return false;

}