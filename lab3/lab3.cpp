#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <vector>
#include <cstring>
#include <iomanip>

struct transport_task {
    transport_task(std::vector<std::vector<uint>> table, std::vector<uint> providers, std::vector<uint> consumers): table{std::move(table)}, providers{std::move(providers)}, consumers{std::move(consumers)}{}
    std::vector<std::vector<uint>> table;
    std::vector<uint> providers;
    std::vector<uint> consumers;
};

transport_task ReadFile(){
    uint m = 0, n = 0;
    std::ifstream input;
    input.open ("input.txt", std::ios::in);
    input >> m >> n;
    std::vector<std::vector<uint>> matrix(m, std::vector<uint>(n, 0));
    std::vector<uint> prov(m, 0);
    std::vector<uint> cons(n, 0);

    for (uint i = 0; i < m; ++i) {
        for (uint j = 0; j < n; ++j) {
            input >> matrix[i][j];
        }
        input >> prov[i];
    }
    for (uint i = 0; i < n; ++i) {
        input >> cons[i];
    }
    input.close();
    return transport_task {matrix, prov, cons};
}

void PrintTable(transport_task &task, std::vector<std::vector<int>> result_table, std::vector<std::vector<bool>> occupation){
    std::cout << std::endl;
    std::cout << std::setw(5) << "Prov";
    for(uint i = 0; i < task.table[0].size(); ++i) {
        std::cout << std::setw(4) << "B" << i + 1;
    }
    std::cout << std::setw(6) << "Stock" << std::endl;
    for(uint i = 0; i < result_table.size(); ++i) {
        std::cout << std::setw(5) << "A"+ std::to_string(i + 1);
        for(uint j = 0; j < result_table[0].size(); ++j) {
            if(!occupation[i][j]) {
                std::cout << std::setw(5) << " ";
            } else {
                if(result_table[i][j] == -1) {
                    std::cout << std::setw(5) << "-";
                    continue;
                }
                std::cout << std::setw(5) << result_table[i][j];
            }
        }
        std::cout << std::setw(5) << task.providers[i] << std::endl;
    }
    std::cout << std::setw(5) << "Need";
    for(uint consumer : task.consumers) {
        std::cout << std::setw(5) << consumer;
    }
    std::cout << std::endl;
}

transport_task checkModel(transport_task task){
    uint prov_sum = 0, cons_sum = 0;
    for(uint provider : task.providers) {
        prov_sum += provider;
    }
    for(uint consumer : task.consumers) {
        cons_sum += consumer;
    }

    if(prov_sum != cons_sum){
        std::cout << "the model is open, let's add a fictitious ";
        if(prov_sum < cons_sum) {
            uint x = cons_sum - prov_sum;
            std::cout << "provider with a stock of " << x;
            std::vector<uint> fict (task.table[0].size(), 0);
            task.table.push_back(fict);
            task.providers.push_back(x);
        } else {
            uint x = prov_sum - cons_sum;
            std::cout << "consuner with need " << x;
            for(auto & i : task.table){
                i.push_back(0);
            }
            task.consumers.push_back(x);
        }
    }
    std::cout << std::endl;
    return task;
}

void FillTableCell(transport_task &task, std::vector<std::vector<int>> &result, std::vector<std::vector<bool>> &occupation, uint cell_i, uint cell_j){
    int cost = std::min(task.providers[cell_i], task.consumers[cell_j]);
    occupation[cell_i][cell_j] = true;
    result[cell_i][cell_j] = cost;

    if(task.providers[cell_i] == cost && task.consumers[cell_j] == cost && cell_i != task.table.size() - 1 && cell_j != task.table[0].size() - 1) {
        result[cell_i][cell_j + 1] = 0;
        occupation[cell_i][cell_j + 1] = true;
    }
    task.providers[cell_i] -= cost;
    task.consumers[cell_j] -= cost;

    if(task.providers[cell_i] == 0) {
        for(auto && j : occupation[cell_i]) {
            j = true;
        }
    }
    if(task.consumers[cell_j] == 0) {
        for(auto && i : occupation) {
            i[cell_j] = true;
        }
    }
}

void NorthWest(transport_task &task){
    std::vector<std::vector<bool>> occupied_table(task.table.size(), std::vector<bool>(task.table[0].size(), false));
    std::vector<std::vector<int>> result_table(task.table.size(), std::vector<int>(task.table[0].size(), -1));

    std::pair<uint, uint> pointer(0, 0);
    for(;;){
        FillTableCell(task, result_table, occupied_table, pointer.first, pointer.second);
        PrintTable(task, result_table, occupied_table);

        if(pointer.first == task.table.size() - 1 && pointer.second == task.table[0].size() - 1) {
            break;
        } else if(occupied_table[pointer.first + 1][pointer.second] && occupied_table[pointer.first][pointer.second + 1] && pointer.first != task.table.size() - 1 && pointer.second != task.table[0].size() - 1) {
            pointer = std::make_pair(pointer.first + 1, pointer.second + 1);
        } else if(occupied_table[pointer.first][pointer.second + 1] || pointer.second == task.table[0].size() - 1) {
            pointer = std::make_pair(pointer.first + 1, pointer.second);
        } else if(occupied_table[pointer.first + 1][pointer.second] || pointer.first == task.table.size() - 1) {
            pointer = std::make_pair(pointer.first, pointer.second + 1);
        }
    }
    uint z = 0, filled_cells_count = 0;
    for(uint i = 0; i < task.table.size(); ++i) {
        for(uint j = 0; j < task.table[i].size(); ++j) {
            if(result_table[i][j] == -1) {
                continue;
            }
            z += result_table[i][j] * task.table[i][j];
            if(result_table[i][j] >= 0) {
                ++filled_cells_count;
            }
        }
    }
    std::cout << std::endl << "Z = " << z << std::endl;
    std::cout << "Cells must be filled: " << task.providers.size() + task.consumers.size() - 1 << " Filled cells: " << filled_cells_count << std::endl;
    if(filled_cells_count == task.providers.size() + task.consumers.size() - 1) {
        std::cout << "Condition met" << std::endl;
    } else {
        std::cout << "Support solution – degenerate" << std::endl;
    }
}

int main() {
    transport_task task = ReadFile();
    task = checkModel(task);
    NorthWest(task);
    return 0;
}
