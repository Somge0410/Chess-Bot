#include <iostream>
#include "Board.h"
#include "utils.h"    
#include "constants.h" 
#include "zobrist.h"
#include "attack_rays.h"
#include "bitboard_masks.h"
#include "MoveGenerator.h"
#include "notation_utils.h"
#include "evaluation.h"
#include "engine.h"
int main(){
    Zobrist::initialize_keys();
    Engine engine;
    Board board;
    
    std::vector<Move> from_new_pos=MoveGenerator::generate_moves(board);
    for(Move move : from_new_pos){
        board.make_move(move);
        board.display();
        board.undo_move(move);
    }
    for (size_t i = 0; i < 7; ++i)
    {
        
        engine.perft_test(board,i);
    }
    std::cout << engine.checks_count << std::endl;
    std::cout << engine.checkmate_count << std::endl;
    std::cout << engine.ep_count << std::endl;
    std::cout << engine.capture_count << std::endl;
    return 0;
    //Board special_board=engine.special_boards[9];
    // special_board.display();
    // std::vector<Move> legal_moves = MoveGenerator::generate_moves(special_board);
    // for(Move move : legal_moves){
    //     special_board.make_move(move);
    //     special_board.display();
    //     special_board.undo_move(move);
    // }
    // for (size_t i = 0; i < 12; ++i)
    // {
    //     Board check_board=engine.check_positions[i];
    //     check_board.display();
    //     std::vector<Move> moves=MoveGenerator::generate_moves(check_board);
    //     std::cout <<moves.size() << std::endl;
    //     for (Move m : moves)
    //     {   
    //         std::string san=to_san(m,moves);
    //         if (san=="axh5")
    //         {
                
    //         std::cout << to_san(m,moves) << std::endl;
    //         check_board.make_move(m);
    //         board.display();
    //         }
            
    //     }
    // }
    
    
    


    


    std::cout << "Choose a color, w for white, b for black" << std::endl;
    char color_choice;
    std::cin >> color_choice;
    Color player_color =(color_choice=='w') ? Color::WHITE : Color::BLACK;  
    
    bool game_running =true;

    while (game_running)
    {
        board.display();
        std::vector<Move> legal_moves = MoveGenerator::generate_moves(board);

        if (legal_moves.empty())
        {
            if (board.in_check())
            {
                std::string winner = board.get_turn() == Color::WHITE ? "Black" : "Whte";
                std::cout << "Checkmate! " << winner << " wins." << std::endl;
            }else
            {
                std::cout << "Stalement! It's a draw." << std::endl;
            }
            game_running=false;
            continue;
        }
        if (board.get_turn() == player_color)
        {
            while (true)
            {
                std::cout << "Your Move: ";
                std::string move_str;
                std::cin >> move_str;

                if (move_str == "exit")
                {
                    game_running =false;
                    break;
                }
                
                Move move_object = parse_move(move_str,legal_moves);
                if (move_object.from_square != -1)
                {
                    board.make_move(move_object);
                    break;
                }else
                {
                    std::cout << "\n!!! Invalid Move. Please try again. !!!\n" << std::endl;
                }
            }
            
        }else
        {
            std::cout << "\nComputer is thinking..." << std::endl;
            Move best_move = engine.search(board,15,30);
            if (best_move.from_square !=-1)
            {
                std::cout << "Computer plays:" << to_san(best_move, legal_moves) << std::endl;
                board.make_move(best_move);
            }else
            {
                std::cout << "Engine cannot find a move. Game over." << std::endl;
                game_running =false;
            }   
        }
    }
    // board.display();
    // legal_moves = MoveGenerator::generate_moves(board);
    // std::cout << "nmb" << legal_moves.size() << std::endl;
    // for (const Move& move : legal_moves)
    // {   
        
    //     board.make_move(move);
    //     std::cout << evaluate(board) << to_san(move,legal_moves)<< std::endl;
    //     board.undo_move(move);
    //     std::cout << evaluate(board) <<std::endl;
    // }
    
    // std::cout << evaluate(board) <<std::endl;
    // board.make_move(parse_move("e4",legal_moves));
    // std::cout << evaluate(board) <<std::endl;
    
    // legal_moves = MoveGenerator::generate_moves(board);
    // board.make_move(parse_move("d5",legal_moves));
    // std::cout << evaluate(board) <<std::endl;

    // legal_moves = MoveGenerator::generate_moves(board);
    // board.make_move(parse_move("e5",legal_moves));
    // std::cout << evaluate(board) <<std::endl;
    

    
    return 0;

}