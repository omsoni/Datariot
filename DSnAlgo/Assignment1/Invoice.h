//
//  Invoice.h
//  Assignment1
//
//  Created by Om Soni on 5/25/18.
//  Copyright © 2018 Om Soni. All rights reserved.
//

#include <string>
#include <stdexcept>
class Invoice {
public:
    Invoice(std::string partNumber, std::string partDesc, int qty, int price)
    : partNumber{partNumber}, partDesc{partDesc} {
        price = price;
        quantity =qty ;
    }
    Invoice() {}
    void setPartNumber(std::string partNo) {
        if (partNo.empty() | (partNo.length() != 8) )
            throw std::invalid_argument( "Invalid Part Number. Valid Parts have  8 letters" );
        partNumber = partNo ;
    }
    std::string getPartNumber() {
        return partNumber ;
    }
    void setPartDesc(std::string desc) {
        if (partDesc.empty())
            partDesc = "No part description provided.";
        partDesc = desc;
    }
    std::string getPartDesc() {
        return partDesc ;
    }
    void setPrice(int price) {
        if ( price < 0 )
            price = 0;
        if (price > 1000)
            throw std::invalid_argument( "Maximum allowed unit price is 1000" );
        this->price = price ;
    }
    int getPrice() {
        return price ;
    }
    void setQuantity(int qty) {
        if (qty < 0)
            qty = 0;
        if (qty > 1000000)
            throw std::invalid_argument( "Maximum allowed quantity is 1000000" );
        this->quantity = qty ;
    }
    int getQuantity() {
        return quantity;
    }
    int64_t getInvoiceAmount() {
        inv_amt = quantity * price ;
        return inv_amt ;
    }
    
    std::string toString() {
        return  "PartNumber: " + partNumber + " PartDesc: "  + partDesc + " Quantity: " + std::to_string(quantity) + " Price per unit: " + std::to_string(price)
        + " Total Invoice Amount: " + std::to_string(inv_amt);
    }
private:
    std::string partNumber ;
    std::string partDesc ;
    int price ;
    int quantity ;
    int64_t inv_amt ;
};
