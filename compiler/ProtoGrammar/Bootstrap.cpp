#include "Grammar.h"


NAMESPACE_OULU_BEGIN


BootstrapGenerator::BootstrapGenerator() {
	
	
}
	
bool BootstrapGenerator::Process(String title, const ParsingUnit& pu) {
	String c_out, h_out;
	
	c_out << "#ifndef flagBOOTSTRAP\n";
	
	c_out << "#include \"Grammar.h\"\n\nnamespace Oulu::" << title << " {\n\n";
	
	Grammar::Parser p;
	
	const Node& n = *pu.root;
	const Node& line_seq = n.At(0);
	
	ASSERT(p.GetNodeTypeString(line_seq) == "FileLineSeq");
	
	for(int i = 0; i < line_seq.GetCount(); i++) {
		const Node& item = line_seq.At(i);
		ASSERT(p.GetNodeTypeString(item) == "FileLineSeqItem");
		
		const Node& file_line = item.At(0);
		ASSERT(p.GetNodeTypeString(file_line) == "FileLine");
		
		const Node& n0 = file_line.At(0);
		
		String type_str = p.GetNodeTypeString(n0);
		
		if (type_str == "CharRuleStmt") {
			String name = n0[0][1][0].GetTokenString();
			LOG("Char rule: " << name);
			
			
		}
		else if (type_str == "TokenRuleStmt") {
			String name = n0[0][1][0].GetTokenString();
			LOG("Token rule: " << name);
			
			
			
		}
		else if (type_str == "RuleExprStmt") {
			String name = n0[0][0][0].GetTokenString();
			String caps_name = ToCaps(name);
			bool make_recur_item = false;
			String i_out; // item out
			
			LOG("Grammar rule: " << name);
			
			const Node& rule_expr = n0[2];
			
			h_out << "bool " << name << "(const Node& n);\n";
			
			c_out << "bool PostParser::" << name << "(const Node& n) {\n";
			c_out << "\tASSERT_TYPE(n, NODE_" << caps_name << ");\n";
			c_out << "\tREF_BLOCK;\n";
			
			i_out << "bool PostParser::" << name << "Item(const Node& n) {\n";
			i_out << "\tASSERT_TYPE(n, NODE_" << caps_name << "_ITEM);\n";
			i_out << "\tREF_BLOCK;\n";
			
			bool lrec = false;
			bool rrec = false;
			
			for(int j = 0; j < rule_expr.GetCount(); j++) {
				const Node& rule_expr_item = rule_expr[j];
				ASSERT(rule_expr_item.GetCount() == (!j ? 1 : 2));
				
				if (!j) {
					c_out << "\tif (IS_BLOCK(" << j << ")) {\n";
					i_out << "\tif (IS_BLOCK(" << j << ")) {\n";
				}
				else {
					c_out << "\telse if (IS_BLOCK(" << j << ")) {\n";
					i_out << "\telse if (IS_BLOCK(" << j << ")) {\n";
				}
				
				
				const Node& block_expr = rule_expr_item[!j ? 0 : 1];
				int rec_id_pos = -1;
				int first_el_pos = -1;
				int last_el_pos = -1;
				bool has_el_post_qual = false;
				int el_count = 0;
				
				for(int k = 0; k < block_expr.GetCount(); k++) {
					const Node& block_expr_item = block_expr[k];
					ASSERT(block_expr_item.GetCount() == 1);
					
					const Node& element_expr = block_expr_item[0];
					
					if (element_expr.GetCount() >= 1) {
						const Node& n0 = element_expr[0];
						String n0_type = p.GetNodeTypeString(n0);
						if (n0_type != "PreExpr" && n0_type != "PostExpr")
							el_count++;
					}
					
					if (element_expr.GetCount() == 2) {
						//const Node& n0 = element_expr[0];
						const Node& n1 = element_expr[1];
						//String n0_type = p.GetNodeTypeString(n0);
						String n1_type = p.GetNodeTypeString(n1);
						
						if (n1_type == "ElementPostQualifier") {
							has_el_post_qual = true;
							break;
						}
					}
				}
				
				if (has_el_post_qual) {
					/*c_out << "\tint p = 0;\n";
					i_out << "\tint p = 0;\n";*/
					c_out << "\t\tDYN_INIT;\n";
					i_out << "\t\tDYN_INIT;\n";
				}
				else {
					c_out << "\t\tASSERT_COUNT(" << el_count << ");\n";
					i_out << "\t\tASSERT_COUNT_NONZERO;\n";
				}
				
				bool inc_dyn = false;
				String prev_pos = "NULL", prev_pos_rec = "NULL";
				for(int k = 0, el_k = 0; k < block_expr.GetCount(); k++) {
					int el_k_rec = (el_k - (rec_id_pos < 0 ? 0 : 1));
					const Node& block_expr_item = block_expr[k];
					ASSERT(block_expr_item.GetCount() == 1);
					
					String pos, pos_rec;
					if (!has_el_post_qual) {
						pos = "SUB" + IntStr(el_k);
						pos_rec = "SUB" + IntStr(el_k_rec);
					}
					else {
						pos = "DYNSUB";
						pos_rec = "DYNSUB";
					}
					
					const Node& element_expr = block_expr_item[0];
					
					if (element_expr.GetCount() == 1) {
						const Node& n0 = element_expr[0];
						String n0_type = p.GetNodeTypeString(n0);
						
						if (n0_type == "Element") {
							if (first_el_pos < 0) first_el_pos = k;
							last_el_pos = k;
							
							if (inc_dyn) {
								inc_dyn = false;
								c_out << "\t\tINC_DYN;\n";
								i_out << "\t\tINC_DYN;\n";
							}
							
							if (n0.GetCount() == 1) {
								const Node& sub_el = n0[0];
								String sub_el_type = p.GetNodeTypeString(sub_el);
								if (sub_el_type == "RuleId") {
									String id = sub_el[0][0].GetTokenTextValue();
									c_out << "\t\t" << id << "(" << pos << ");\n";
									
									if (id == name)
										rec_id_pos = k;
									else
										i_out << "\t\t" << id << "(" << pos_rec << ");\n";
								}
								else if (sub_el_type == "CharLiteral") {
									String lit = sub_el[0].GetTokenString();
									c_out << "\t\tPOST_TEST(TestCharLiteral(" << pos << ", \"" << lit << "\"));\n";
									i_out << "\t\tPOST_TEST(TestCharLiteral(" << pos_rec << ", \"" << lit << "\"));\n";
								}
								else if (sub_el_type == "StringLiteral") {
									String lit = sub_el[0].GetTokenString();
									c_out << "\t\tPOST_TEST(TestStringLiteral(" << pos << ", \"" << lit << "\"));\n";
									i_out << "\t\tPOST_TEST(TestStringLiteral(" << pos_rec << ", \"" << lit << "\"));\n";
								}
								else {
									TODO
								}
							}
							else {
								TODO
							}
							
							prev_pos     = "&" + pos;
							if (rec_id_pos != k) prev_pos_rec = "&" + pos_rec;
							el_k++;
							inc_dyn = has_el_post_qual;
						}
						else if (n0_type == "PostExpr") {
							ASSERT(n0.GetCount() == 4);
							const Node& id_seq = n0[2];
							String cmd;
							for(int l = 0; l < id_seq.GetCount(); l++) {
								const Node& id = id_seq[l];
								ASSERT(id.GetCount() == 1);
								if (l) cmd.Cat(' ');
								cmd << id[0][0].GetTokenTextValue();
							}
							int cmd_len = cmd.GetCount();
							
							c_out << "\t\tPushCommand(\"" << cmd << "\", " << cmd_len << ");\n";
							i_out << "\t\tPushCommand(\"" << cmd << "\", " << cmd_len << ");\n";
						}
						else if (n0_type == "PreExpr") {
							TODO
						}
						else {
							TODO
						}
					}
					else if (element_expr.GetCount() == 2) {
						const Node& n0 = element_expr[0];
						const Node& n1 = element_expr[1];
						String n0_type = p.GetNodeTypeString(n0);
						String n1_type = p.GetNodeTypeString(n1);
						
						
						if (n0_type == "Element" && n0.GetCount() == 1 && n1_type == "ElementPostQualifier") {
							const Node& sub_el = n0[0];
							String sub_el_type = p.GetNodeTypeString(sub_el);
							String qualifier_str = n1[0].GetTokenTextValue();
							
							if (inc_dyn) {
								inc_dyn = false;
								c_out << "\t\tINC_DYN;\n";
								i_out << "\t\tINC_DYN;\n";
							}
							if (qualifier_str == "*") {
								c_out << "\t\tTODO;\n";
								i_out << "\t\tTODO;\n";
							}
							else if (qualifier_str == "+") {
								c_out << "\t\tTODO;\n";
								i_out << "\t\tTODO;\n";
							}
							else if (qualifier_str == "?") {
								if (sub_el_type == "RuleId") {
									String id = sub_el[0][0].GetTokenTextValue();
									c_out << "\t\tif (IS_NOT_END && IS_TYPE_SUBDYN(NODE_" << ToCaps(id) << ")) {" << id << "(DYNSUB); INC_DYN;}\n";
									
									if (id == name)
										rec_id_pos = k;
									else
										i_out << "\t\tif (IS_NOT_END && IS_TYPE_SUBDYN(NODE_" << ToCaps(id) << ")) {" << id << "(DYNSUB); INC_DYN;}\n";
								}
								else if (sub_el_type == "CharLiteral") {
									String lit = sub_el[0].GetTokenString();
									c_out << "\t\tif (IS_NOT_END && IS_TYPE_SUBDYN(NODE_CHAR_LITERAL)) {POST_TEST(CharLiteral(SUB_DYN_INC, \"" << lit << "\"));}\n";
									i_out << "\t\tif (IS_NOT_END && IS_TYPE_SUBDYN(NODE_CHAR_LITERAL)) {POST_TEST(PassCharLiteral(SUB_DYN_INC, \"" << lit << "\"));}\n";
								}
								else if (sub_el_type == "StringLiteral") {
									String lit = sub_el[0].GetTokenString();
									c_out << "\t\tif (IS_NOT_END && IS_TYPE_SUBDYN(NODE_STRING_LITERAL)) {POST_TEST(PassStringLiteral(SUB_DYN_INC, \"" << lit << "\"));}\n";
									i_out << "\t\tif (IS_NOT_END && IS_TYPE_SUBDYN(NODE_STRING_LITERAL)) {POST_TEST(PassStringLiteral(SUB_DYN_INC, \"" << lit << "\"));}\n";
								}
								else {
									TODO
								}
							}
							else {
								TODO
							}
							
							prev_pos     = "&" + pos;
							prev_pos_rec = "&" + pos_rec;
							el_k++;
							inc_dyn = has_el_post_qual;
						}
						else {
							TODO
						}
					}
					else {
						TODO
					}
					
				}
				
				if (rec_id_pos >= 0) {
					if (rec_id_pos == first_el_pos)
						lrec = true;
					else if (rec_id_pos == last_el_pos)
						rrec = true;
					else {
						LOG("error: invalid recursive pos");
						return false;
					}
				}
				c_out << "\t\treturn true;\n\t}\n";
				i_out << "\t\treturn true;\n\t}\n";
			}
			
			
			
			
			if (lrec) {
				c_out << "\telse if (IS_BLOCK(-1)) {\n";
				c_out << "\t\tfor(int i = 0; i < n.GetCount(); i++) {\n";
				c_out << "\t\t\tPOST_TEST(" << name << "Item(SUB(i)));\n";
				c_out << "\t\t}\n";
				c_out << "\t\treturn true;\n";
				c_out << "\t}\n";
				make_recur_item = true;
			}
			else if (rrec) {
				TODO
			}
			
			if (rule_expr.GetCount()) {
				c_out << "\telse {ADD_POST_ERROR(\"Invalid block in " << name << "\");}\n";
				i_out << "\telse {ADD_POST_ERROR(\"Invalid block in " << name << "\");}\n";
			}
			
			c_out << "\treturn false;\n}\n\n";
			i_out << "\treturn false;\n}\n\n";
			
			
			if (make_recur_item) {
				h_out << "bool " << name << "Item(const Node& n);\n";
				c_out << i_out;
			}
		}
		
	}
	
	c_out << "}\n\n";
	
	c_out << "#endif\n\n";
	
	
	
	FileOut file_h_out(GetDataFile("Generated_" + title + "Post.inl"));
	FileOut file_c_out(GetDataFile("Generated_" + title + "Post.cpp"));
	
	file_h_out << h_out;
	file_c_out << c_out;
	
	file_h_out.Close();
	file_c_out.Close();
	
	return true;
}


NAMESPACE_OULU_END
